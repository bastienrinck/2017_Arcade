#include <cstddef>
#include "Color.hpp"

/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include "PixelBox.hpp"

Arcade::PixelBox::PixelBox(size_t height, size_t width, size_t posW, size_t posH
)
{
	_size.setXY(width, height);
	_pos.setXY(posW, posH);
}

unsigned long Arcade::PixelBox::getH() const
{
	return _size.getY();
}

unsigned long Arcade::PixelBox::getPosH() const
{
	return _pos.getY();
}

void Arcade::PixelBox::setH(size_t height)
{
	_size.setY();
}

void Arcade::PixelBox::setPosH(size_t posH)
{
	_pos.setY();
}

unsigned long Arcade::PixelBox::getW() const
{
	return _size.getX();
}

unsigned long Arcade::PixelBox::getPosW() const
{
	return _pos.getX();
}

void Arcade::PixelBox::setW(size_t width)
{
	_size.setX();
}

void Arcade::PixelBox::setPosW(size_t posW)
{
	_pos.setX();
}

void Arcade::PixelBox::setColor(Color &color)
{
	_color = color;
}

Arcade::Color &Arcade::PixelBox::getColor()
{
	return _color;
}

void Arcade::PixelBox::setSprite(void *sprite)
{
	_sprite = sprite;
}

void *Arcade::PixelBox::getSprite()
{
	return _sprite;
}
