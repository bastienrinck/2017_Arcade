/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include "TextBox.hpp"

Arcade::TextBox::TextBox(const std::string &text, size_t h, size_t w,
	size_t posH, size_t posW
)
{
	_value = text;
	_size.setXY(w, h);
	_pos.setXY(posW, posH);
}

std::__cxx11::basic_string<char> Arcade::TextBox::getValue() const
{
	return _value;
}

void Arcade::TextBox::setValue(const std::string &text)
{
	_value = text;
}

void *Arcade::TextBox::getFont() const
{
	return _font;
}

void Arcade::TextBox::setFont(void *font)
{
	_font = font;
}

unsigned long Arcade::TextBox::getH() const
{
	return _size.getY();
}

unsigned long Arcade::TextBox::getPosH() const
{
	return _pos.getY();
}

void Arcade::TextBox::setH(size_t heigh)
{
	_size.setY(heigh);
}

void Arcade::TextBox::setPosH(size_t posH)
{
	_pos.setY(posH);
}

unsigned long Arcade::TextBox::getW() const
{
	return _size.getX();
}

unsigned long Arcade::TextBox::getPosW() const
{
	return _pos.getX();
}

void Arcade::TextBox::setW(size_t width)
{
	_size.setX(width);
}

void Arcade::TextBox::setPosW(size_t posW)
{
	_pos.setX(posW);
}
