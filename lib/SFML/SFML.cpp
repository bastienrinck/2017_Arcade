/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "SFML.hpp"

Arcade::IGraphicLib *lib = nullptr;

__attribute__((constructor)) void init()
{
	lib = new Arcade::sfml;
}

__attribute__((destructor)) void destruct()
{
	delete lib;
}

extern "C" Arcade::IGraphicLib *entryPoint(void)
{
	return lib;
}

Arcade::sfml::sfml()
{
	_window.setFramerateLimit(30);
	_texture.create(1920, 1080);
	_sprite.setTexture(_texture);
	_font.loadFromFile("ressources/fonts/Times New Roman.ttf");
};

Arcade::sfml::~sfml() = default;

std::string Arcade::sfml::getName() const
{
	return _name;
}

bool Arcade::sfml::isOpen() const
{
	return _window.isOpen();
}

void Arcade::sfml::closeRenderer()
{
	_window.close();
}

void Arcade::sfml::openRenderer(std::string const &title)
{

	_window.create(sf::VideoMode(1920, 1080), "Arcade");
}

void Arcade::sfml::clearWindow()
{
	_window.clear();
}

void Arcade::sfml::refreshWindow()
{
	_window.display();
}

void Arcade::sfml::drawPixelBox(Arcade::PixelBox &pB)
{
	_texture.update((unsigned char *)&pB.getPixelArray()[0],
		static_cast<unsigned int>(pB.getWidth()),
		static_cast<unsigned int>(pB.getHeight()),
		static_cast<unsigned int>(pB.getX()),
		static_cast<unsigned int>(pB.getY()));
	_sprite.setTextureRect(sf::Rect<int>(static_cast<int>(pB.getX()),
		static_cast<int>(pB.getY()), static_cast<int>(pB.getWidth()),
		static_cast<int>(pB.getHeight())));
	_sprite.setPosition(pB.getX(), pB.getY());
	_window.draw(_sprite);
}

void Arcade::sfml::drawText(Arcade::TextBox &tB)
{
	_text.setFont(_font);
	_text.setString(tB.getValue());
	_text.setCharacterSize(static_cast<unsigned int>(tB.getFontSize()));
	_text.setFillColor(*(sf::Color *)((unsigned char *)tB.getColor()));
	_text.setOutlineThickness(0.2);
	_text.setOutlineColor(
		*(sf::Color *)((unsigned char *)tB.getBackgroundColor()));
	_text.setPosition(tB.getPos().getX(), tB.getPos().getY());
	_window.draw(_text);
}

Arcade::Keys Arcade::sfml::getLastEvent()
{
	Arcade::Keys key = Arcade::Keys::NONE;

	if (!_events.empty()) {
		key = _events.front();
		_events.pop_front();
	}
	return key;
}

bool Arcade::sfml::pollEvents()
{
	auto event = sf::Event();
	bool ret = false;

	while (_window.pollEvent(event)) {
		if (_keyMap.count(event.key.code)) {
			_events.push_back(_keyMap.at(event.key.code));
			ret = true;
		}
	}
	return ret;
}

void Arcade::sfml::clearEvents()
{
	_events.clear();
}

Arcade::Vect<size_t> Arcade::sfml::getScreenSize() const
{
	auto mode = sf::VideoMode::getDesktopMode();

	return {mode.width, mode.height};
}

size_t Arcade::sfml::getMaxY() const
{
	return sf::VideoMode::getDesktopMode().height;
}

size_t Arcade::sfml::getMaxX() const
{
	return sf::VideoMode::getDesktopMode().width;
}
