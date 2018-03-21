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

	auto *pixel = new Arcade::PixelBox(10, 10, 10, 10);
	auto *text = new Arcade::TextBox("Salut les copains\n", 10, 10, 10, 10);
	Arcade::Color color(100, 100, 100, 0);
	for (size_t i = 0; i < 10; i++)
		for (size_t k = 0; k < 10; k++) {
			Arcade::Vect<size_t> pos(i, k);
			pixel->putPixel(pos, color);
		}
	_currentLib->getInstance()->openRendering();
	_currentLib->getInstance()->drawText(text);
	_currentLib->getInstance()->refreshWindow();
	usleep(1000000);
	_currentLib->getInstance()->clearWindow();
	_currentLib->getInstance()->drawPixelBox(pixel);
	_currentLib->getInstance()->refreshWindow();
	usleep(10000000);
	_currentLib->getInstance()->closeRendering();
	return ret;
}

bool Arcade::Core::loadGame()
{
	_currentGame = new DLLoader<IGameModule>(_games[_gidx], "./games/");
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
