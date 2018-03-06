/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <iostream>
#include "core.hpp"

Core::Core(std::string name)
{
	for (unsigned it = 0; it < libsNames.size() && _lidx == UINT_MAX; it++)
		_lidx = libsNames[it] == name ? it : _lidx;
	if (_lidx == UINT_MAX)
		std::cerr << name + ": Invalid library name" << std::endl;
}

bool Core::start()
{
	bool ret = true;

	if (_lidx == UINT_MAX)
		ret = false;
	else if (!load_lib() || !load_game(0))
		ret = false;
	return ret;
}

bool Core::load_game(unsigned idx)
{
	auto dlloader = DLLoader<IGames>(games[idx], "./games/");
	auto currentGame(dlloader.getInstance());
	_currentGame = currentGame;
	if (currentGame)
		std::cout << "Game [" << _currentGame->getName() << "] loaded !"
			<< std::endl;
	else
		std::cerr << "Unable to load game [" << gamesNames[idx] << "]..." << std::endl;
	return currentGame != nullptr;
}

bool Core::load_lib()
{
	auto dlloader = DLLoader<IGraphicalLib>(libs[_lidx], "./lib/");
	auto currentLib(dlloader.getInstance());
	_currentLib = currentLib;
	if (currentLib)
		std::cout << "Lib [" << currentLib->getName() << "] loaded !"
			<< std::endl;
	else
		std::cout << "Unable to load lib [" << libs[_lidx] << "]..." << std::endl;
	return currentLib != nullptr;
}
