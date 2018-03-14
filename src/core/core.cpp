/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <iostream>
#include <dirent.h>
#include <regex>
#include "core.hpp"

Arcade::Core::Core(std::string name)
{
	inspectDirectory("./lib", _libs);
	inspectDirectory("./games", _games);
	_gidx = _games.empty() ? UINT_MAX : 0;
	for (unsigned it = 0; it < _libs.size() && _lidx == UINT_MAX; it++)
		_lidx = _libs[it] == name ? it : _lidx;
	if (_lidx == UINT_MAX)
		std::cerr << name + ": Invalid library name" << std::endl;
}

Arcade::Core::~Core() = default;

bool Arcade::Core::start()
{
	bool ret = true;

	if (_lidx == UINT_MAX || _gidx == UINT_MAX) {
		if (_gidx == UINT_MAX)
			std::cerr << "No games found in ./games directory"
				<< std::endl;
		ret = false;
	} else if (!loadLib() || !loadGame())
		ret = false;
	return ret;
}

bool Arcade::Core::loadGame()
{
	auto dlloader = DLLoader<IGameModule>(_games[_gidx], "./games/");
	auto currentGame(dlloader.getInstance());
	_currentGame = currentGame;
	if (currentGame)
		std::cout << "Game [" << _currentGame->getName() << "] loaded !"
			<< std::endl;
	else
		std::cerr << "Unable to load game [" << _games[_gidx] << "]..."
			<< std::endl;
	return currentGame != nullptr;
}

bool Arcade::Core::loadLib()
{
	auto dlloader = DLLoader<IGraphicLib>(_libs[_lidx], "./lib/");
	auto currentLib(dlloader.getInstance());
	_currentLib = currentLib;
	if (currentLib)
		std::cout << "Lib [" << currentLib->getName() << "] loaded !"
			<< std::endl;
	else
		std::cout << "Unable to load lib [" << _libs[_lidx] << "]..."
			<< std::endl;
	return currentLib != nullptr;
}

bool Arcade::Core::inspectDirectory(std::string &&dir, std::vector<std::string> &vec)
{
	struct dirent **list;
	std::smatch m;
	int n;

	n = scandir(dir.c_str(), &list, nullptr, alphasort);
	for (int i = 0; i < n; i++)
		if (std::regex_match(list[i]->d_name, std::regex("(.+.so)")))
			vec.emplace_back(list[i]->d_name);
	std::cout << "List :\n";
	for (const auto &i : vec)
		std::cout << i << std::endl;
	return !vec.empty();
}
