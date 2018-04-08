/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <iostream>
#include <zconf.h>
#include "TextBox.hpp"
#include "Core.hpp"

Arcade::Core::Core(std::string name)
{
	bool ret;

	std::cout << "Loading libs:" << std::endl;
	ret = inspectDirectory("./lib/", _libs);
	if (ret)
		std::cout << std::endl << "Loading games:" << std::endl;
	if (ret && inspectDirectory("./games/", _games)) {
		_menu.setLists(&_games, &_libs);
		if (_libs.empty())
			std::cerr << "No libs found in ./libs directory"
				<< std::endl;
		if (_games.empty())
			std::cerr << "No games found in ./games directory"
				<< std::endl;
		for (unsigned i = 0; i < _libs.size(); ++i)
			_lidx = (_libs[i]->getFilePath().find(name, 0) !=
				std::string::npos) ? i : _lidx;
		if (_lidx == UINT_MAX)
			std::cerr << "Library " << name << " not found"
				<< std::endl;
	}
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
		std::cout << "Lib " << library->getInstance()->getName()
			<< " loaded" << std::endl << std::endl;
		list.push_back(library);
	}
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
		std::cout << "Loading " << name << "..." << std::endl;
		if (!loadLib(name, dir, vec))
			return false;
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
		} else if (!_games[_gidx]->getInstance()->applyEvent(key))
			return false;
	}
	return true;
}

size_t Arcade::Core::getLibIdx() const
{
	return _lidx;
}

bool Arcade::Core::start()
{
	for (auto &cell : _games) {
		std::string gameName = cell->getInstance()->getName();
		_score.addGame(gameName);
	}
	_libs[_lidx]->getInstance()->openRenderer("Arcade");
	for (bool ret = true; !_exit; ret = true) {
		if (_libs[_lidx]->getInstance()->pollEvents())
			ret = applyKeys(
				(_gidx == UINT_MAX) ? _menuActions : _actions);
		if (ret && _gidx != UINT_MAX) {
			ret = _games[_gidx]->getInstance()->update();
			_games[_gidx]->getInstance()->refresh(
				*_libs[_lidx]->getInstance());
		} else
			_menu.refresh(_libs[_lidx]->getInstance(), _lidx,
				_score);
		if (!ret) {
			updateScore();
			_gidx = UINT_MAX;
		}
	}
	return true;
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
	updateScore();
	_libs[_lidx]->getInstance()->closeRenderer();
	_games[_gidx]->getInstance()->stop();
	_gidx = (!_gidx) ? static_cast<unsigned int>(_games.size() - 1) :
		_gidx - 1;
	_libs[_lidx]->getInstance()->openRenderer("Arcade");
	_games[_gidx]->getInstance()->init();
	return true;
}

bool Arcade::Core::nextGame()
{
	updateScore();
	_libs[_lidx]->getInstance()->closeRenderer();
	_games[_gidx]->getInstance()->stop();
	_gidx = (_gidx == _games.size() - 1) ? 0 : _gidx + 1;
	_libs[_lidx]->getInstance()->openRenderer("Arcade");
	_games[_gidx]->getInstance()->init();
	return true;
}

bool Arcade::Core::restartGame()
{
	updateScore();
	if (_gidx != UINT_MAX) {
		_games[_gidx]->getInstance()->init();
		_games[_gidx]->getInstance()->refresh(
			*_libs[_lidx]->getInstance());
	}
	return true;
}

bool Arcade::Core::backMenu()
{
	updateScore();
	if (_gidx != UINT_MAX) {
		_games[_gidx]->getInstance()->stop();
		_menu.refresh(_libs[_lidx]->getInstance(), _lidx, _score);
	}
	_gidx = UINT_MAX;
	return true;
}

bool Arcade::Core::exit()
{
	updateScore();
	std::cout << "exit" << std::endl;
	_exit = true;
	return false;
}

void Arcade::Core::updateScore()
{
	if (_gidx != UINT_MAX) {
		std::string game = _games[_gidx]->getInstance()->getName();
		std::string name = _menu.getUserName();
		auto score = static_cast<int>(_games[_gidx]->getInstance()->getScore());

		if (score > _score.getPlayerScore(game, name))
			_score.setScore(game, name,
				static_cast<unsigned int>(score));
	}
}
