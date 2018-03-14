/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include "nCurses.hpp"

lib_nCurses::lib_nCurses() = default;

lib_nCurses::~lib_nCurses() = default;

std::string lib_nCurses::getName()
{
	return _name;
}

bool lib_nCurses::supportSprite() const
{
	return false;
}

bool lib_nCurses::supportSound() const
{
	return false;
}

bool lib_nCurses::needFont() const
{
	return false;
}

bool lib_nCurses::isOpen() const
{
	return false;
}

bool lib_nCurses::closeRendering()
{
	return false;
}

bool lib_nCurses::openRendering()
{
	return false;
}

void lib_nCurses::clearWindow()
{
}

bool lib_nCurses::initRenderer()
{
	return false;
}

bool lib_nCurses::stopRenderer()
{
	return false;
}

void lib_nCurses::drawPixelBox(Arcade::PixelBox *)
{
}

void lib_nCurses::drawText(Arcade::TextBox *)
{
}

void lib_nCurses::playSound(void *)
{
}

void lib_nCurses::pauseSound(void *)
{
}

void lib_nCurses::stopSound(void *)
{
}

void *lib_nCurses::loadTextFont(std::string path)
{
	return nullptr;
}

void *lib_nCurses::loadSprite(std::string path)
{
	return nullptr;
}

void *lib_nCurses::loadSound(std::string path)
{
	return nullptr;
}

Arcade::Keys lib_nCurses::getLastEvent()
{
	return {};
}

void lib_nCurses::pollEvent()
{
}

void lib_nCurses::cleanEvent()
{
}

Arcade::Vect<size_t> lib_nCurses::getScreenSize() const
{
	return {};
}

int lib_nCurses::getMaxY() const
{
	return 0;
}

int lib_nCurses::getMaxX() const
{
	return 0;
}
