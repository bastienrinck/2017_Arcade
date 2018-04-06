/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <string>
#include <zconf.h>
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
	static int idx = 0;
	auto r = Arcade::PixelBox(Arcade::Vect<size_t>(gl.getMaxX(), gl.getMaxY()), Vect<size_t>(), Arcade::Color(255, 0, 0, 255));
	auto g = Arcade::PixelBox(Arcade::Vect<size_t>(gl.getMaxX(), gl.getMaxY()), Vect<size_t>(), Arcade::Color(0, 255, 0, 255));
	auto b = Arcade::PixelBox(Arcade::Vect<size_t>(gl.getMaxX(), gl.getMaxY()), Vect<size_t>(), Arcade::Color(0, 0, 255, 255));

	gl.clearWindow();
	if (idx == 0)
		gl.drawText(_tB);
	else if (idx == 1)
		gl.drawPixelBox(r);
	else if (idx == 2)
		gl.drawPixelBox(g);
	else if (idx == 3)
		gl.drawPixelBox(b);
	gl.refreshWindow();
	idx = idx == 3 ? 0 : idx + 1;
}

size_t Arcade::Pacman::getScore()
{
	return 0;
}
