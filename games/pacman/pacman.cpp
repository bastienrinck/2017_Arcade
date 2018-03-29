/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <string>
#include "pacman.hpp"

Pacman::Pacman() = default;

Pacman::~Pacman() = default;

const std::string &Pacman::getName() const
{
	return _name;
}

bool Pacman::init()
{
	return false;
}

bool Pacman::stop()
{
	return false;
}

bool Pacman::close()
{
	return false;
}

bool Pacman::open()
{
	return false;
}

bool Pacman::loop(Arcade::IGraphicLib *graphicsLib)
{
	return false;
}