/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/
#include "SFML.hpp"

SFML::SFML() = default;

SFML::~SFML() = default;

std::string SFML::getName()
{
	return _name;
}

bool SFML::supportSprite() const
{
	return false;
}

bool SFML::supportSound() const
{
	return false;
}

bool SFML::needFont() const
{
	return false;
}

bool SFML::isOpen() const
{
	return false;
}

bool SFML::closeRendering()
{
	return false;
}

bool SFML::openRendering()
{
	return false;
}

void SFML::clearWindow()
{
}

void SFML::refreshWindow()
{
}

bool SFML::initRenderer()
{
	return false;
}

bool SFML::stopRenderer()
{
	return false;
}

void SFML::drawPixelBox(Arcade::PixelBox *)
{
}

void SFML::drawText(Arcade::TextBox *)
{
}

void SFML::playSound(void *)
{
}

void SFML::pauseSound(void *)
{
}

void SFML::stopSound(void *)
{
}

void *SFML::loadTextFont(std::string)
{
	return nullptr;
}

void *SFML::loadSprite(std::string)
{
	return nullptr;
}

void *SFML::loadSound(std::string)
{
	return nullptr;
}

Arcade::Keys SFML::getLastEvent()
{
	return {};
}

bool SFML::pollEvent()
{
	return false;
}

void SFML::cleanEvent()
{
}

Arcade::Vect<size_t> SFML::getScreenSize() const
{
	return {};
}

int SFML::getMaxY() const
{
	return 0;
}

int SFML::getMaxX() const
{
	return 0;
}
