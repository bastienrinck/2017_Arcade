/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/
#include <ctime>
#include <unordered_map>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "snake.hpp"

#define CELL_WIDTH 10
#define CELL_HEIGHT 10

Arcade::IGameLib *lib = nullptr;

__attribute__((constructor)) void init()
{
	lib = new Arcade::snake;
}

__attribute__((destructor)) void destruct()
{
	delete lib;
}

extern "C" Arcade::IGameLib *entryPoint(void)
{
	return lib;
}

const std::string Arcade::snake::getName() const
{
	return _name;
}

bool Arcade::snake::init()
{
	_map.resize(_height * _width);
	_snake.clear();
	_direction = 2;
	_snake.emplace_back(Arcade::Vect<size_t>(_width / 2 - 2, _height / 2));
	_snake.emplace_back(Arcade::Vect<size_t>(_width / 2 - 1, _height / 2));
	_snake.emplace_back(Arcade::Vect<size_t>(_width / 2, _height / 2));
	_snake.emplace_back(Arcade::Vect<size_t>(_width / 2 + 1, _height / 2));
	return true;
}

bool Arcade::snake::stop()
{
	return true;
}

bool Arcade::snake::moveUp()
{
	if (!_snake.front().getY() || _direction == 1)
		return false;
	_snake.push_front(Arcade::Vect<size_t>(_snake.front().getX(),
		_snake.front().getY() - 1));
	_snake.pop_back();
	_direction = 0;
	return true;
}

bool Arcade::snake::moveDown()
{
	if (_snake.front().getY() + 1 == _height || _direction == 0)
		return false;
	_snake.push_front(Arcade::Vect<size_t>(_snake.front().getX(),
		_snake.front().getY() + 1));
	_snake.pop_back();
	_direction = 1;
	return true;
}

bool Arcade::snake::moveLeft()
{
	if (!_snake.front().getX() || _direction == 3)
		return false;
	_snake.push_front(Arcade::Vect<size_t>(_snake.front().getX() - 1,
		_snake.front().getY()));
	_snake.pop_back();
	_direction = 2;
	return true;
}

bool Arcade::snake::moveRight()
{
	if (!_snake.front().getX() + 1 == _width || _direction == 2)
		return false;
	_snake.push_front(Arcade::Vect<size_t>(_snake.front().getX() + 1,
		_snake.front().getY()));
	_snake.pop_back();
	_direction = 3;
	return true;
}

void Arcade::snake::print_background(Arcade::IGraphicLib &graphicsLib
)
{
	Arcade::Vect<size_t> dimension = graphicsLib.getScreenSize();

	_pB = Arcade::PixelBox(Arcade::Vect<size_t>(_width * CELL_WIDTH,
		_height * CELL_HEIGHT), Arcade::Vect<size_t>(
		(dimension.getX() / 2) - (_width * CELL_WIDTH / 2),
		(dimension.getY() / 2) - (_height * CELL_HEIGHT / 2)),
		Arcade::Color(255, 255, 255, 255));
	graphicsLib.drawPixelBox(_pB);
}

bool Arcade::snake::applyEvent(Arcade::Keys key)
{
	std::unordered_map<Arcade::Keys, size_t> action = {
		{Arcade::Keys::Z, 0}, {Arcade::Keys::S, 1},
		{Arcade::Keys::Q, 2}, {Arcade::Keys::D	, 3}};
	bool (Arcade::snake::*moveArr[4])() = {&Arcade::snake::moveUp,
		&Arcade::snake::moveDown, &Arcade::snake::moveLeft,
		&Arcade::snake::moveRight};

	if (action.count(key))
		(this->*moveArr[action.at(key)])();
	return true;
}

bool Arcade::snake::update()
{
	static auto timer = std::time(nullptr);
	auto currentTimer = std::time(nullptr);
	bool (Arcade::snake::*moveArr[4])() = {&Arcade::snake::moveUp,
		&Arcade::snake::moveDown, &Arcade::snake::moveLeft,
		&Arcade::snake::moveRight};

	if (timer < currentTimer) {
		timer = currentTimer;
		(this->*moveArr[_direction])();
	}
	return true;
}

void Arcade::snake::refresh(Arcade::IGraphicLib &graphicsLib)
{

	size_t pWidth = _width * CELL_WIDTH;
	size_t pHeight = _height * CELL_HEIGHT;

	graphicsLib.clearWindow();
	print_background(graphicsLib);
	_pB = Arcade::PixelBox(Arcade::Vect<size_t>(CELL_WIDTH, CELL_HEIGHT),
		Arcade::Vect<size_t>(), Arcade::Color(255, 0, 0, 255));
	for (auto cell : _snake) {
		_pB.setX((graphicsLib.getMaxX() / 2) - (pWidth / 2) +
			(cell.getX() * CELL_WIDTH));
		_pB.setY((graphicsLib.getMaxY() / 2) - (pHeight / 2) +
			(cell.getY() * CELL_HEIGHT));
		graphicsLib.drawPixelBox(_pB);
	}
	graphicsLib.refreshWindow();
}

size_t Arcade::snake::getScore()
{
	return 0;
}
