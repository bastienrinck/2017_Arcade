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
	_menu.setLists(&_games, &_libs);
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
	for (auto &_game : _games)
		delete _game;
}

template<typename T>
bool Arcade::Core::loadLib(std::string &name, std::string &dir,
	std::vector<DLLoader<T> *> &list
)
{
	auto library = new DLLoader<T>(name, dir);

	if (library->getInstance()) {
		std::string libname(library->getInstance()->getName());
		std::cout << "Lib [" << libname << "] loaded !" << std::endl;
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
		} else if (_gidx == UINT_MAX) {
			if ((_gidx = _menu.applyEvent(key)) != UINT_MAX) {
				_games[_gidx]->getInstance()->init();
				_libs[_lidx]->getInstance()->clearWindow();
			}
		} else
			_games[_gidx]->getInstance()->applyEvent(key);
	}
	return true;
}

bool Arcade::Core::start()
{
	bool ret = true;
	std::unordered_map<Arcade::Keys, bool (Core::*)()> actions = {
		{Arcade::Keys::LEFT, &Core::prevLibG},
		{Arcade::Keys::RIGHT, &Core::nextLibG},
		{Arcade::Keys::DOWN, &Core::prevGame},
		{Arcade::Keys::UP, &Core::nextGame},
		{Arcade::Keys::SPACE, &Core::restartGame},
		{Arcade::Keys::BACKSPACE, &Core::backMenu},
		{Arcade::Keys::ESC, &Core::exit}};
	std::unordered_map<Arcade::Keys, bool (Core::*)()> menuActions = {
		{Arcade::Keys::LEFT, &Core::prevLibG},
		{Arcade::Keys::RIGHT, &Core::nextLibG},
		{Arcade::Keys::ESC, &Core::exit}};

	_libs[_lidx]->getInstance()->openRenderer("Arcade");
	while (ret) {
		if (_libs[_lidx]->getInstance()->pollEvents())
			ret = applyKeys(
				(_gidx == UINT_MAX) ? menuActions : actions);
		if (ret && _gidx != UINT_MAX) {
			ret = _games[_gidx]->getInstance()->update();
			_games[_gidx]->getInstance()->refresh(
				*_libs[_lidx]->getInstance());
		} else
			_menu.refresh(_libs[_lidx]->getInstance(), _lidx);
	}
}

bool Arcade::Core::prevLibG()
{
	_libs[_lidx]->getInstance()->closeRenderer();
	_lidx = (!_lidx) ? static_cast<unsigned int>(_libs.size() - 1) :
		_lidx - 1;
	_libs[_lidx]->getInstance()->openRenderer("Arcade");
	return true;
}

bool Arcade::Core::nextLibG()
{
	_libs[_lidx]->getInstance()->closeRenderer();
	_lidx = (_lidx == _libs.size() - 1) ? 0 : _lidx + 1;
	_libs[_lidx]->getInstance()->openRenderer("Arcade");
	return true;
}

bool Arcade::Core::prevGame()
{
	_libs[_lidx]->getInstance()->closeRenderer();
	_games[_gidx]->getInstance()->stop();
	_gidx = (!_gidx) ? static_cast<unsigned int>(_games.size() - 1) :
		_gidx - 1;
	_games[_gidx]->getInstance()->init();
	_libs[_lidx]->getInstance()->openRenderer("Arcade");
	return true;
}

bool Arcade::Core::nextGame()
{
	_libs[_lidx]->getInstance()->closeRenderer();
	_games[_gidx]->getInstance()->stop();
	_gidx = (_gidx == _games.size() - 1) ? 0 : _gidx + 1;
	_games[_gidx]->getInstance()->init();
	_libs[_lidx]->getInstance()->openRenderer("Arcade");
	return true;
}

bool Arcade::Core::restartGame()
{
	if (_gidx != UINT_MAX) {
		_games[_gidx]->getInstance()->init();
		_games[_gidx]->getInstance()->refresh(
			*_libs[_lidx]->getInstance());
	}
	return true;
}

bool Arcade::Core::backMenu()
{
	if (_gidx != UINT_MAX) {
		_games[_gidx]->getInstance()->stop();
		_menu.refresh(_libs[_lidx]->getInstance(), _lidx);
	}
	_gidx = UINT_MAX;
	return true;
}

bool Arcade::Core::exit()
{
	std::cout << "exit" << std::endl;
	return false;
}

void Arcade::Menu::printBackground(Arcade::IGraphicLib *gl,
	Arcade::Vect<size_t> &mode
)
{
	auto background = Arcade::PixelBox(mode, Arcade::Vect<size_t>(0, 0),
		Arcade::Color(0, 0, 0, 255));
	auto backgroundMenu = Arcade::PixelBox(
		Arcade::Vect<size_t>(mode.getX() / 10 * 4,
			mode.getY() / 5 * 4));

	gl->drawPixelBox(background);
	backgroundMenu.setX(mode.getX() / 20);
	backgroundMenu.setY(mode.getY() / 20);
	gl->drawPixelBox(backgroundMenu);
	backgroundMenu.setX(mode.getX() / 20 + mode.getX() / 2);
	gl->drawPixelBox(backgroundMenu);
}

void Arcade::Menu::printGames(Arcade::IGraphicLib *gl,
	Arcade::Vect<size_t> &mode
)
{
	auto select = Arcade::Color(128, 0, 0, 255);
	auto other = Arcade::Color(0, 0, 0, 255);
	auto text = Arcade::TextBox("", Arcade::Vect<size_t>(0, 0));

	text.setBackgroundColor(Arcade::Color(221, 221, 221, 255));
	for (unsigned i = 0; i < _games->size(); ++i) {
		text.setValue((*_games)[i]->getInstance()->getName());
		text.setY(static_cast<size_t>(
			mode.getY() * 0.1 +
				(i * (_games->size() * mode.getY() * 0.04))));
		text.setX(mode.getX() / 10);
		text.setColor(_idx == i ? select : other);
		gl->drawText(text);
	}
}

void Arcade::Menu::printLibs(Arcade::IGraphicLib *gl,
	Arcade::Vect<size_t> &mode, unsigned idx
)
{
	auto select = Arcade::Color(128, 0, 0, 255);
	auto other = Arcade::Color(0, 0, 0, 255);
	auto text = Arcade::TextBox("", Arcade::Vect<size_t>(0, 0));

	text.setBackgroundColor(Arcade::Color(221, 221, 221, 255));
	for (unsigned i = 0; i < _libs->size(); ++i) {
		text.setValue((*_libs)[i]->getInstance()->getName());
		text.setX(mode.getX() / 2);
		text.setY(static_cast<size_t>(
			mode.getY() * 0.1 +
				(i * (_libs->size() * mode.getY() * 0.04))));
		text.setColor(idx == i ? select : other);
		text.setX(mode.getX() / 10 + mode.getX() / 2);
		gl->drawText(text);
	}
}

void Arcade::Menu::refresh(Arcade::IGraphicLib *gl, unsigned idx)
{
	auto mode = gl->getScreenSize();
	auto text = Arcade::TextBox(_username, Arcade::Vect<size_t>(0, 0));

	gl->clearWindow();
	printBackground(gl, mode);
	gl->drawText(text);
	printGames(gl, mode);
	printLibs(gl, mode, idx);
	gl->refreshWindow();
}

unsigned Arcade::Menu::applyEvent(Arcade::Keys key)
{
	const char keysC[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
		'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z'};

	if (key == Arcade::Keys::UP && _idx < _games->size() - 1)
		_idx += 1;
	else if (key == Arcade::Keys::DOWN && _idx > 0)
		_idx -= 1;
	else if (key < 26)
		_username += keysC[key - 1];
	else if (key == Arcade::Keys::BACKSPACE && !_username.empty())
		_username.pop_back();
	return (key == Arcade::Keys::ENTER) ? _idx : UINT_MAX;
}

void Arcade::Menu::setLists(std::vector<DLLoader<Arcade::IGameLib> *> *games,
	std::vector<DLLoader<Arcade::IGraphicLib> *> *libs
)
{
	_games = games;
	_libs = libs;
}
