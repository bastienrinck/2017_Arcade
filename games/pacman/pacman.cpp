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

const std::string &Arcade::Pacman::getName() const
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

bool Arcade::Pacman::close()
{
	return true;
}

bool Arcade::Pacman::open()
{
	return true;
}

void Arcade::Pacman::applyEvent(Arcade::Keys)
{
}

void Arcade::Pacman::update()
{
}

void Arcade::Pacman::refresh(Arcade::IGraphicLib *gl)
{
	auto tB = Arcade::TextBox(_name, Arcade::Vect<size_t>(0, 0));

	gl->drawText(tB);
	gl->clearWindow();
	gl->refreshWindow();
}
