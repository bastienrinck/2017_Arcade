/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/
#include <ctime>
#include <unordered_map>
#include <iostream>
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

const std::string &Arcade::snake::getName() const
{
	return _name;
}

bool Arcade::snake::init()
{
	//_timer = std::time(nullptr);
	_map.resize(_height * _width);
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

bool Arcade::snake::close()
{
	return true;
}

bool Arcade::snake::open()
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

void Arcade::snake::print_background(Arcade::IGraphicLib *graphicsLib)
{
	Arcade::PixelBox pB;
	Arcade::Vect<size_t> dimension = graphicsLib->getScreenSize();

	pB.setHeight(_height * CELL_HEIGHT);
	pB.setWidth(_width * CELL_WIDTH);
	pB.setX((dimension.getX() / 2) - (pB.getWidth() / 2));
	pB.setY((dimension.getY() / 2) - (pB.getHeight() / 2));
	graphicsLib->drawPixelBox(pB);
	std::cout << "sizeX :" << pB.getWidth() << std::endl;
	std::cout << "offsetX :" << pB.getX() << std::endl;
	std::cout << "sizeY :" << pB.getHeight() << std::endl;
	std::cout << "offsetY :" << pB.getY() << std::endl;
}

void Arcade::snake::applyEvent(Arcade::Keys key)
{
	std::unordered_map<Arcade::Keys, size_t> action = {
		{Arcade::Keys::UP, 0}, {Arcade::Keys::DOWN, 1},
		{Arcade::Keys::LEFT, 2}, {Arcade::Keys::RIGHT, 3}};
	bool (Arcade::snake::*moveArr[4])() = {&Arcade::snake::moveUp,
		&Arcade::snake::moveDown, &Arcade::snake::moveLeft,
		&Arcade::snake::moveRight};

	if (action.count(key))
		(this->*moveArr[action.at(key)])();
}

void Arcade::snake::update()
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
}

void Arcade::snake::refresh(Arcade::IGraphicLib *graphicsLib)
{
	Arcade::PixelBox pB(Arcade::Vect<size_t>(CELL_WIDTH, CELL_HEIGHT),
		Arcade::Vect<size_t>(), Arcade::Color());
	size_t pWith = _width * CELL_WIDTH;
	size_t pHeight = _height * CELL_HEIGHT;

	std::cout << "[calc] : start" << std::endl;
	graphicsLib->clearWindow();
	print_background(graphicsLib);
	std::cout << "[calc] : BG done" << std::endl;
	for (auto cell : _snake) {
		pB.setX(graphicsLib->getMaxX() / 2 - pWith / 2 +
			cell.getX() * CELL_WIDTH);
		pB.setY(graphicsLib->getMaxY() / 2 - pHeight / 2 +
			cell.getY() * CELL_HEIGHT);
		graphicsLib->drawPixelBox(pB);
	}
	graphicsLib->refreshWindow();
	std::cout << "[calc] : done" << std::endl;
}