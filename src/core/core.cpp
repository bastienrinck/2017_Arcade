/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <iostream>
#include <zconf.h>
#include "TextBox.hpp"
#include "core.hpp"

Arcade::Core::Core(std::string name)
{
	std::cout << "Loading libs and games:" << std::endl;
	inspectDirectory("./lib/", _libs);
	inspectDirectory("./games/", _games);
	_menu.setList(&_games);
	if (_libs.empty())
		throw std::logic_error("No libs found in ./libs directory");
	if (_games.empty())
		throw std::logic_error("No games found in ./games directory");
	for (unsigned i = 0; i < _libs.size(); ++i)
		_lidx = (_libs[i]->getFilePath().find(name, 0) !=
			std::string::npos) ? i : _lidx;
	if (_lidx == UINT_MAX)
		throw std::logic_error(name + ": Invalid library name");
	std::cout << "Lib " << name << " founded, name :"
		<< _libs[_lidx]->getFilePath() << std::endl;
}

Arcade::Core::~Core()
{
	for (auto &_lib : _libs) {
		if (_lib->getInstance()->isOpen())
			_lib->getInstance()->closeRenderer();
		delete _lib;
	}
	for (auto &_game : _games) {
		_game->getInstance()->close();
		delete _game;
	}
}

template<typename T>
bool Arcade::Core::loadLib(std::string &name, std::string &dir,
	std::vector<DLLoader<T> *> &list
)
{
	auto library = new DLLoader<T>(name, dir);

	if (library->getInstance()) {
		std::cout << "Lib [" << library->getInstance()->getName()
			<< "] loaded !" << std::endl;
		list.push_back(library);
	} else
		throw std::runtime_error(
			"Unable to load lib [" + name + "]...");
	return library->getInstance() != nullptr;
}

template<typename T>
bool Arcade::Core::inspectDirectory(std::string &&dir,
	std::vector<DLLoader<T> *> &vec
)
{
	int n;
	std::smatch m;
	struct dirent **list;
	auto filter = [](const struct dirent *entry) {
		return static_cast<int>(std::regex_match(entry->d_name,
			std::regex("(.+.so)")));
	};

	n = scandir(dir.c_str(), &list, filter, alphasort);
	for (int i = 0; i < n; i++) {
		std::string name(list[i]->d_name);
		loadLib(name, dir, vec);
		free(list[i]);
	}
	return !vec.empty();
}

bool Arcade::Core::applyKeys(
	std::unordered_map<Arcade::Keys, bool (Core::*)()> &actions
)
{
	Arcade::Keys key;

	while ((key = _libs[_lidx]->getInstance()->getLastEvent()) !=
		Arcade::Keys::NONE) {
		_libs[_lidx]->getInstance()->clearEvents();
		if (actions.count(key)) {
			return (this->*actions[key])();
		} else if (_gidx == UINT_MAX)
			_gidx = _menu.applyEvent(key);
		else
			_games[_gidx]->getInstance()->applyEvent(key);
	}
	return true;
}

bool Arcade::Core::start()
{
	bool ret = true;
	std::unordered_map<Arcade::Keys, bool (Core::*)()> actions = {
		{Arcade::Keys::Q, &Core::prevLibG},
		{Arcade::Keys::D, &Core::nextLibG},
		{Arcade::Keys::S, &Core::prevGame},
		{Arcade::Keys::Z, &Core::nextGame},
		{Arcade::Keys::R, &Core::restartGame},
		{Arcade::Keys::BACKSPACE, &Core::backMenu},
		{Arcade::Keys::ESC, &Core::exit}};

	_libs[_lidx]->getInstance()->openRenderer();
	while (ret) {
		if (_libs[_lidx]->getInstance()->pollEvents())
			ret = applyKeys(actions);
		if (_gidx != UINT_MAX) {
			_games[_gidx]->getInstance()->update();
			_games[_gidx]->getInstance()->refresh(
				_libs[_lidx]->getInstance());
		} else
			_menu.refresh(_libs[_lidx]->getInstance());
	}
}

bool Arcade::Core::prevLibG()
{
	/*_currentLib->getInstance()->closeRenderer();
	delete _currentLib;
	_lidx = (!_lidx) ? static_cast<unsigned int>(_libs.size() - 1) : _lidx - 1;
	loadLib();
	_currentLib->getInstance()->openRenderer();
	 */
	return true;
}

bool Arcade::Core::nextLibG()
{
	/*_currentLib->getInstance()->closeRenderer();
	delete _currentLib;
	_lidx = (_lidx == _libs.size() - 1) ? 0 : _lidx + 1;
	loadLib();
	_currentLib->getInstance()->openRenderer();
	return true;*/
	return true;
}

bool Arcade::Core::prevGame()
{
	_libs[_lidx]->getInstance()->closeRenderer();
	_games[_gidx]->getInstance()->stop();
	_gidx = (!_gidx) ? static_cast<unsigned int>(_games.size() - 1) : _gidx - 1;
	_games[_gidx]->getInstance()->init();
	_libs[_lidx]->getInstance()->openRenderer();
	return true;
}

bool Arcade::Core::nextGame()
{
	_libs[_lidx]->getInstance()->closeRenderer();
	_games[_gidx]->getInstance()->stop();
	_gidx = (_gidx == _games.size() - 1) ? 0 : _gidx + 1;
	_games[_gidx]->getInstance()->init();
	_libs[_lidx]->getInstance()->openRenderer();
	return true;
}

bool Arcade::Core::restartGame()
{
	if (_gidx != UINT_MAX) {
		_games[_gidx]->getInstance()->init();
		_games[_gidx]->getInstance()->refresh(_libs[_lidx]->getInstance());
	}
	return true;
}

bool Arcade::Core::backMenu()
{
	if (_gidx != UINT_MAX) {
		_games[_gidx]->getInstance()->stop();
		_menu.refresh(_libs[_lidx]->getInstance());
	}
	_gidx = UINT_MAX;
	return true;
}

bool Arcade::Core::exit()
{
	std::cout << "exit" << std::endl;
	return false;
}

void Arcade::Menu::refresh(Arcade::IGraphicLib *gl)
{
	auto select = Arcade::Color(128, 0, 0, 255);
	auto other = Arcade::Color(255, 255, 255, 255);
	auto mode = gl->getScreenSize();
	auto background = Arcade::PixelBox(mode, Arcade::Vect<size_t>(0, 0),
		Arcade::Color(206, 206, 206, 120));
	auto text = Arcade::TextBox("", Arcade::Vect<size_t>(0, 0));

	gl->clearWindow();
	gl->drawPixelBox(background);
	for (unsigned i = 0; i < _list->size(); ++i) {
		text.setValue((*_list)[i]->getInstance()->getName());
		text.setY(
			(mode.getY() - _list->size() * 50) / 2 + (i * 50 + 10));
		text.setColor(_idx == i ? select : other);
		gl->drawText(text);
	}
	gl->refreshWindow();
}

unsigned Arcade::Menu::applyEvent(Arcade::Keys key)
{
	if (key == Arcade::Keys::DOWN && _idx < _list->size() - 1)
		_idx += 1;
	else if (key == Arcade::Keys::UP && _idx > 0)
		_idx -= 1;
	return (key == Arcade::Keys::ENTER) ? _idx : UINT_MAX;
}

void Arcade::Menu::setList(std::vector<DLLoader<Arcade::IGameLib> *> *list)
{
	_list = list;
}
