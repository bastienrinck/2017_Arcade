/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/
#include <ctime>
#include <unordered_map>
#include <iostream>
#include "nibbler.hpp"

#define WIDTH 41
#define HEIGHT 20

static std::vector<std::string> map = {
	"                                         ",
	" *****                             ***** ",
	" ***                                 *** ",
	"                                         ",
	"     **  ***********************  **     ",
	"     *                             *     ",
	"                                         ",
	"    *              ****             *    ",
	"    *              ****             *    ",
	"    *              ****             *    ",
	"    *      ********************     *    ",
	"    *      ********************     *    ",
	"    *              ****             *    ",
	"    *              ****             *    ",
	"                   ****                  ",
	"     *                             *     ",
	"     **  ***********************  **     ",
	" ***                                 *** ",
	" *****                             ***** ",
	"                                         ",};

Arcade::IGameLib *lib = nullptr;

__attribute__((constructor)) void init()
{
	lib = new Arcade::Nibbler;
}

__attribute__((destructor)) void destruct()
{
	delete lib;
}

extern "C" Arcade::IGameLib *entryPoint(void)
{
	return lib;
}

const std::string Arcade::Nibbler::getName() const
{
	return _name;
}

bool Arcade::Nibbler::init()
{
	_snake.clear();
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	_direction = 2;
	_snake.emplace_back(
		Arcade::Vect<size_t>(WIDTH / 2 - 2, HEIGHT / 2 + 9));
	_snake.emplace_back(
		Arcade::Vect<size_t>(WIDTH / 2 - 1, HEIGHT / 2 + 9));
	_snake.emplace_back(Arcade::Vect<size_t>(WIDTH / 2, HEIGHT / 2 + 9));
	_snake.emplace_back(
		Arcade::Vect<size_t>(WIDTH / 2 + 1, HEIGHT / 2 + 9));
	_score = 0;
	return true;
}

bool Arcade::Nibbler::stop()
{
	return true;
}

bool Arcade::Nibbler::lost()
{
	for (std::list<Arcade::Vect<size_t>>::const_iterator cell = _snake.begin(), end = _snake.end();
		cell != end; ++cell) {
		if (map[cell->getY()][cell->getX()] == '*')
			return false;
		else if (_snake.begin() != cell &&
			_snake.begin()->getX() == cell->getX() &&
			_snake.begin()->getY() == cell->getY())
			return false;
	}
	return true;
}

void Arcade::Nibbler::check_bonus()
{
	if (_bonus.getX() != _snake.front().getX() ||
		_bonus.getY() != _snake.front().getY())
		return;
	for (bool ret = true; ret;) {
		_bonus.setX(static_cast<size_t>(std::rand() % WIDTH));
		_bonus.setY(static_cast<size_t>(std::rand() % HEIGHT));
		for (std::list<Arcade::Vect<size_t>>::const_iterator cell = _snake.begin(), end = _snake.end();
			cell != end; ++cell) {
			if ((map[_bonus.getY()][_bonus.getX()] == '*') ||
				(cell->getX() == _bonus.getX() &&
					cell->getY() == _bonus.getY()))
				break;
		}
		ret = false;
	}
	_score += 100;
}

bool Arcade::Nibbler::moveUp()
{
	if (!_snake.front().getY())
		return false;
	else if (_direction != 1) {
		_snake.push_front(Arcade::Vect<size_t>(_snake.front().getX(),
			_snake.front().getY() - 1));
		if (_bonus.getX() != _snake.front().getX() ||
			_bonus.getY() != _snake.front().getY())
			_snake.pop_back();
		_direction = 0;
		_timer = std::time(nullptr);
		check_bonus();
	}
	return lost();
}

bool Arcade::Nibbler::moveDown()
{
	if (_snake.front().getY() == HEIGHT - 1)
		return false;
	else if (_direction) {
		_snake.push_front(Arcade::Vect<size_t>(_snake.front().getX(),
			_snake.front().getY() + 1));
		if (_bonus.getX() != _snake.front().getX() ||
			_bonus.getY() != _snake.front().getY())
			_snake.pop_back();
		_direction = 1;
		_timer = std::time(nullptr);
		check_bonus();
	}
	return lost();
}

bool Arcade::Nibbler::moveLeft()
{
	if (!_snake.front().getX())
		return false;
	else if (_direction != 3) {
		_snake.push_front(
			Arcade::Vect<size_t>(_snake.front().getX() - 1,
				_snake.front().getY()));
		if (_bonus.getX() != _snake.front().getX() ||
			_bonus.getY() != _snake.front().getY())
			_snake.pop_back();
		_direction = 2;
		_timer = std::time(nullptr);
		check_bonus();
	}
	return lost();
}

bool Arcade::Nibbler::moveRight()
{
	if (_snake.front().getX() == WIDTH - 1)
		return false;
	else if (_direction != 2) {
		_snake.push_front(
			Arcade::Vect<size_t>(_snake.front().getX() + 1,
				_snake.front().getY()));
		if (_bonus.getX() != _snake.front().getX() ||
			_bonus.getY() != _snake.front().getY())
			_snake.pop_back();
		_direction = 3;
		_timer = std::time(nullptr);
		check_bonus();
	}
	return lost();
}

void Arcade::Nibbler::print_map(Arcade::IGraphicLib &graphicsLib,
	Arcade::Vect<size_t> const &res
)
{
	auto pWidth = static_cast<size_t>(res.getX() * 0.6 / WIDTH);
	auto pHeight = static_cast<size_t>(res.getY() * 0.6 / HEIGHT);
	auto offsetX = static_cast<size_t>(res.getX() * 0.3);
	auto offsetY = static_cast<size_t>(res.getY() * 0.3);

	for (unsigned i = 0; i < map.size(); ++i) {
		for (unsigned j = 0; j < map[i].size(); ++j) {
			if (map[i][j] == '*')
				_pB = Arcade::PixelBox(
					Arcade::Vect<size_t>(pWidth, pHeight),
					Arcade::Vect<size_t>(),
					Arcade::Color(76, 38, 114, 255));
			else
				_pB = Arcade::PixelBox(
					Arcade::Vect<size_t>(pWidth, pHeight),
					Arcade::Vect<size_t>(),
					Arcade::Color(255, 255, 255, 255));
			_pB.setX(offsetX + j * pWidth);
			_pB.setY(offsetY + i * pHeight);
			graphicsLib.drawPixelBox(_pB);
		}
	}
}

bool Arcade::Nibbler::applyEvent(Arcade::Keys key)
{
	std::unordered_map<Arcade::Keys, size_t> action = {{Arcade::Keys::Z, 0},
		{Arcade::Keys::S, 1}, {Arcade::Keys::Q, 2},
		{Arcade::Keys::D, 3}};
	bool (Arcade::Nibbler::*moveArr[4])() = {&Arcade::Nibbler::moveUp,
		&Arcade::Nibbler::moveDown, &Arcade::Nibbler::moveLeft,
		&Arcade::Nibbler::moveRight};

	if (action.count(key))
		return (this->*moveArr[action.at(key)])();
	return true;
}

bool Arcade::Nibbler::update()
{

	auto currentTimer = std::time(nullptr);
	bool (Arcade::Nibbler::*moveArr[4])() = {&Arcade::Nibbler::moveUp,
		&Arcade::Nibbler::moveDown, &Arcade::Nibbler::moveLeft,
		&Arcade::Nibbler::moveRight};

	if (_timer < currentTimer) {
		_timer = currentTimer;
		return (this->*moveArr[_direction])();
	}
	return true;
}

void Arcade::Nibbler::refresh(Arcade::IGraphicLib &graphicsLib)
{
	Arcade::Vect<size_t> res = graphicsLib.getScreenSize();
	auto pWidth = static_cast<size_t>(res.getX() * 0.6 / WIDTH);
	auto pHeight = static_cast<size_t>(res.getY() * 0.6 / HEIGHT);
	auto offsetX = static_cast<size_t>(res.getX() * 0.3);
	auto offsetY = static_cast<size_t>(res.getY() * 0.3);
	auto text = Arcade::TextBox("Score : " + std::to_string(_score),
		Arcade::Vect<size_t>());

	graphicsLib.clearWindow();
	print_map(graphicsLib, res);
	_pB = Arcade::PixelBox(Arcade::Vect<size_t>(pWidth, pHeight),
		Arcade::Vect<size_t>(), Arcade::Color(191, 63, 63, 255));
	for (auto cell : _snake) {
		_pB.setX(offsetX + cell.getX() * pWidth);
		_pB.setY(offsetY + cell.getY() * pHeight);
		graphicsLib.drawPixelBox(_pB);
	}

	_pB = Arcade::PixelBox(Arcade::Vect<size_t>(pWidth, pHeight),
		Arcade::Vect<size_t>(offsetX + _bonus.getX() * pWidth,
			offsetY + _bonus.getY() * pHeight),
		Arcade::Color(255, 0, 0, 255));
	graphicsLib.drawPixelBox(_pB);
	graphicsLib.drawText(text);
	graphicsLib.refreshWindow();
}

size_t Arcade::Nibbler::getScore()
{
	return static_cast<size_t>(_score);
}
