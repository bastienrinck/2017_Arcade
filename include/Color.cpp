/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include "Color.hpp"

Arcade::Color::Color(unsigned char red, unsigned char green, unsigned char blue,
	unsigned char alpha
) : _red(red), _green(green), _blue(blue), _alpha(alpha)
{
}

void Arcade::Color::setColor(unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha
)
{
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha;
}

unsigned char Arcade::Color::getRed() const
{
	return _red;
}

unsigned char Arcade::Color::getGreen() const
{
	return _green;
}

unsigned char Arcade::Color::getBlue() const
{
	return _blue;
}

unsigned char Arcade::Color::getAlpha() const
{
	return _alpha;
}

void Arcade::Color::setRed(unsigned char red)
{
	_red = red;
}

void Arcade::Color::setGreen(unsigned char green)
{
	_green = green;
}

void Arcade::Color::setBlue(unsigned char blue)
{
	_blue = blue;
}

void Arcade::Color::setAlpha(unsigned char alpha)
{
	_alpha = alpha;
}

Arcade::Color::operator unsigned char *()
{
	return &_red;
}

bool Arcade::Color::operator==(const Arcade::Color &other) const
{
	return _red == other.getRed() && _green == other.getGreen() &&
		_blue == other.getBlue() && _alpha == other.getAlpha();
}
