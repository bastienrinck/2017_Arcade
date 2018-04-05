/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <string>
#include "pacman.hpp"

Arcade::IGameLib *lib = nullptr;

__attribute__((constructor)) void init()
{
	lib = new Arcade::Pacman;
}

__attribute__((destructor)) void destruct()
{
	delete lib;
}

extern "C" Arcade::IGameLib *entryPoint(void)
{
	return lib;
}

const std::string Arcade::Pacman::getName() const
{
	return _name;
}

bool Arcade::Pacman::init()
{
	return true;
}

bool Arcade::Pacman::stop()
{
	return true;
}

bool Arcade::Pacman::applyEvent(Arcade::Keys)
{
	return true;
}

bool Arcade::Pacman::update()
{
	return true;
}

void Arcade::Pacman::refresh(Arcade::IGraphicLib &gl)
{
	gl.clearWindow();
	gl.drawText(_tB);
	gl.refreshWindow();
}

size_t Arcade::Pacman::getScore()
{
	return 0;
}
