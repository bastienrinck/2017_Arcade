#include <cstddef>
#include "Color.hpp"

/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include "PixelBox.hpp"

Arcade::PixelBox::PixelBox(size_t height, size_t width, size_t posW,
	size_t posH
)
{
	_size.setXY(width, height);
	_pos.setXY(posW, posH);
}

size_t Arcade::PixelBox::getHeight() const
{
	return _size.getY();
}

size_t Arcade::PixelBox::getY() const
{
	return _pos.getY();
}

void Arcade::PixelBox::setHeight(size_t height)
{
	_size.setY(height);
}

void Arcade::PixelBox::setY(size_t y)
{
	_pos.setY(y);
}

size_t Arcade::PixelBox::getWidth() const
{
	return _size.getX();
}

size_t Arcade::PixelBox::getX() const
{
	return _pos.getX();
}

void Arcade::PixelBox::setWidth(size_t width)
{
	_size.setX(width);
}

void Arcade::PixelBox::setX(size_t x)
{
	_pos.setX(x);
}

void Arcade::PixelBox::putPixel(Arcade::Vect<size_t> pos, Arcade::Color col)
{
	_colorTab[pos] = col;
}

Arcade::Color Arcade::PixelBox::getPixel(Arcade::Vect<size_t> pos)
{
	return _colorTab[pos];
}

std::vector<Arcade::Color> Arcade::PixelBox::getPixelArray()
{
	std::vector<Arcade::Color> pixelArray;
	Arcade::Vect<size_t> pos;

	for(size_t i = 0; i < getHeight(); i++)
		for(size_t j = 0; j < getWidth(); j++){
			pos.setXY(j, i);
			pixelArray.push_back(_colorTab[pos]);
		}
	return pixelArray;
}

std::unordered_map<Arcade::Vect<size_t>, Arcade::Color> &Arcade::PixelBox::getPixelMap()
{
	return _colorTab;
}
