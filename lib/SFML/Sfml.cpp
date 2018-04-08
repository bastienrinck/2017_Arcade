/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sfml.hpp"

Arcade::IGraphicLib *lib = nullptr;

__attribute__((constructor)) void init()
{
	lib = new Arcade::Sfml;
}

__attribute__((destructor)) void destruct()
{
	delete lib;
}

extern "C" Arcade::IGraphicLib *entryPoint(void)
{
	return lib;
}

Arcade::Sfml::Sfml()
{
	_window.setFramerateLimit(30);
	_texture.create(1920, 1080);
	_sprite.setTexture(_texture);
	_font.loadFromFile("resources/fonts/font.ttf");
};

Arcade::Sfml::~Sfml() = default;

std::string Arcade::Sfml::getName() const
{
	return _name;
}

bool Arcade::Sfml::isOpen() const
{
	return _window.isOpen();
}

void Arcade::Sfml::closeRenderer()
{
	_window.close();
}

void Arcade::Sfml::openRenderer(std::string const &title)
{

	_window.create(sf::VideoMode(1280, 720), title);
}

void Arcade::Sfml::clearWindow()
{
	_window.clear();
}

void Arcade::Sfml::refreshWindow()
{
	_window.display();
}

void Arcade::Sfml::drawPixelBox(Arcade::PixelBox const &pB)
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

void Arcade::Sfml::drawText(Arcade::TextBox const &tB)
{
	_text.setFont(_font);
	_text.setString(tB.getValue());
	_text.setCharacterSize(static_cast<unsigned int>(tB.getFontSize()));
	_text.setFillColor(*(sf::Color *)((unsigned char *)tB.getColor()));
	_text.setOutlineThickness(0.4);
	_text.setOutlineColor(
		*(sf::Color *)((unsigned char *)tB.getBackgroundColor()));
	_text.setPosition(tB.getPos().getX(), tB.getPos().getY());
	_window.draw(_text);
}

Arcade::Keys Arcade::Sfml::getLastEvent()
{
	Arcade::Keys key = Arcade::Keys::NONE;

	if (!_events.empty()) {
		key = _events.front();
		_events.pop_front();
	}
	return key;
}

bool Arcade::Sfml::pollEvents()
{
	auto event = sf::Event();
	bool ret = false;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed)
			if (_keyMap.count(event.key.code)) {
				_events.push_back(_keyMap.at(event.key.code));
				ret = true;
			}
		if (event.type == sf::Event::Resized) {
			sf::FloatRect visibleArea(0, 0, event.size.width,
				event.size.height);
			_window.setView(sf::View(visibleArea));
		}
	}
	return ret;
}

void Arcade::Sfml::clearEvents()
{
	_events.clear();
}

Arcade::Vect<size_t> Arcade::Sfml::getScreenSize() const
{
	auto mode = _window.getSize();

	return {mode.x, mode.y};
}

size_t Arcade::Sfml::getMaxY() const
{
	return _window.getSize().y;
}

size_t Arcade::Sfml::getMaxX() const
{
	return _window.getSize().x;
}
