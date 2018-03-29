/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <iostream>
#include <dirent.h>
#include <regex>
#include "TextBox.hpp"
#include <zconf.h>
#include "core.hpp"

Arcade::Core::Core(std::string name)
{
	std::cout << "Loading libs and games:" << std::endl;
	inspectDirectory("./lib", _libs);
	inspectDirectory("./games", _games);
	if (_libs.empty())
		throw std::logic_error("No libs found in ./libs directory");
	if (_games.empty())
		throw std::logic_error("No games found in ./games directory");
	for (unsigned it = 0; it < _libs.size() && _lidx == UINT_MAX; it++)
		_lidx = _libs[it] == name ? it : _lidx;
	if (_lidx == UINT_MAX)
		throw std::logic_error(name + ": Invalid library name");
}

Arcade::Core::~Core()
{
	delete _currentLib;
	delete _currentGame;
};

bool Arcade::Core::start()
{
	bool ret = true;

	if (!loadLib() || !loadGame())
		ret = false;

	Arcade::PixelBox box(Vect<size_t>(300, 200), Vect<size_t>(100, 100),
		Color(0, 100, 100, 255));
	Arcade::PixelBox box2(Vect<size_t>(300, 200), Vect<size_t>(150, 150),
		Color(0, 100, 0, 255));
	Arcade::TextBox txt("Test, Bonsoir les amis !!", Vect<size_t>(400, 300),
		45, Color(255, 255, 255, 100), Color(200, 200, 200, 255));

	_currentLib->getInstance()->openRenderer();
	_currentLib->getInstance()->drawPixelBox(box);
	_currentLib->getInstance()->drawPixelBox(box2);
	_currentLib->getInstance()->drawText(txt);
	_currentLib->getInstance()->refreshWindow();
	sleep(5);
	_currentLib->getInstance()->closeRenderer();
	sleep(2);
	_currentLib->getInstance()->openRenderer();
	sleep(2);
	_currentLib->getInstance()->closeRenderer();
	return ret;
}

bool Arcade::Core::loadGame()
{
	_currentGame = new DLLoader<IGameLib>(_games[_gidx], "./games/");
	if (_currentGame->getInstance())
		std::cout << "Game [" << _currentGame->getInstance()->getName()
			<< "] loaded !" << std::endl;
	else
		std::cerr << "Unable to load game [" << _games[_gidx] << "]..."
			<< std::endl;
	return _currentGame->getInstance() != nullptr;
}

bool Arcade::Core::loadLib()
{
	_currentLib = new DLLoader<IGraphicLib>(_libs[_lidx], "./lib/");
	if (_currentLib->getInstance())
		std::cout << "Lib [" << _currentLib->getInstance()->getName()
			<< "] loaded !" << std::endl;
	else
		std::cout << "Unable to load lib [" << _libs[_lidx] << "]..."
			<< std::endl;
	return _currentLib->getInstance() != nullptr;
}

bool Arcade::Core::inspectDirectory(std::string &&dir,
	std::vector<std::string> &vec
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
	std::cout << "  " << dir << ":" << std::endl;

	for (int i = 0; i < n; i++) {
		vec.emplace_back(std::string("./") + list[i]->d_name);
		std::cout << "\t  " << vec[vec.size() - 1] << std::endl;
		free(list[i]);
	}
	std::cout << std::endl;
	return !vec.empty();
}
