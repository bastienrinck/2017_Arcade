/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <ncurses.h>
#include "nCurses.hpp"

lib_nCurses::lib_nCurses() = default;

lib_nCurses::~lib_nCurses() = default;

std::string lib_nCurses::getName()
{
	return _name;
}

bool lib_nCurses::supportSprite() const
{
	return false;
}

bool lib_nCurses::supportSound() const
{
	return false;
}

bool lib_nCurses::needFont() const
{
	return false;
}

bool lib_nCurses::isOpen() const
{
	return _isOpen;
}

bool lib_nCurses::closeRendering()
{
	delwin(_win);
	endwin();
	return true;
}

bool lib_nCurses::openRendering()
{
	int h, w;

	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, true);
	getmaxyx(stdscr, h, w);
	_win = newwin(h, w, 0, 0);
	return true;
}

void lib_nCurses::clearWindow()
{
	clear();
}

void lib_nCurses::refreshWindow()
{
	wrefresh(_win);
}

bool lib_nCurses::initRenderer()
{
	return true;
}

bool lib_nCurses::stopRenderer()
{
	return true;
}

void lib_nCurses::drawPixelBox(Arcade::PixelBox *pB)
{
	for (size_t i = 0; i < pB->getHeight(); i++) {
		for (size_t j = 0; j < pB->getWidth(); j++) {
			Arcade::Vect<size_t> pos(j, i);
			auto pp = pB->getPixel(pos);
			mvwprintw(_win, static_cast<int>(pos.getY()),
				static_cast<int>(pos.getY()),
				"\\033[48;2;%d;%d;%dm%c\\033[0m", pp.getRed(),
				pp.getGreen(), pp.getBlue(), ' ');
		}
	}
}

void lib_nCurses::drawText(Arcade::TextBox *tB)
{
	mvwprintw(_win, static_cast<int>(tB->getPosH()),
		static_cast<int>(tB->getPosW()), "%s", tB->getValue());
}

void lib_nCurses::playSound(void *)
{
}

void lib_nCurses::pauseSound(void *)
{
}

void lib_nCurses::stopSound(void *)
{
}

void *lib_nCurses::loadTextFont(std::string)
{
	return nullptr;
}

void *lib_nCurses::loadSprite(std::string)
{
	return nullptr;
}

void *lib_nCurses::loadSound(std::string)
{
	return nullptr;
}

Arcade::Keys lib_nCurses::getLastEvent()
{
	return _lastEvent;
}

bool lib_nCurses::pollEvent()
{
	const Arcade::Keys _keyNames[] = {Arcade::NONE, Arcade::A, Arcade::B,
		Arcade::C, Arcade::D, Arcade::E, Arcade::F, Arcade::G,
		Arcade::H, Arcade::I, Arcade::J, Arcade::K, Arcade::L,
		Arcade::M, Arcade::N, Arcade::O, Arcade::P, Arcade::Q,
		Arcade::R, Arcade::S, Arcade::T, Arcade::U, Arcade::V,
		Arcade::W, Arcade::X, Arcade::Y, Arcade::Z, Arcade::LEFT,
		Arcade::RIGHT, Arcade::UP, Arcade::DOWN, Arcade::ENTER,
		Arcade::SPACE, Arcade::DELETE, Arcade::BACKSPACE, Arcade::TAB,
		Arcade::ESC};
	const int keys[] = {ERR, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
		'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN,
		KEY_ENTER, ' ', KEY_BACKSPACE, '\t', 27};

	_lastEvent = Arcade::Keys::NONE;
	for (auto i : keys)
		if (i) {
			_lastEvent = _keyNames[i];
			break;
		}
	return true;
}

void lib_nCurses::cleanEvent()
{
	_lastEvent = Arcade::NONE;
}

Arcade::Vect<size_t> lib_nCurses::getScreenSize() const
{
	Arcade::Vect<size_t> resolution;

	resolution.setXY(static_cast<size_t>(LINES), static_cast<size_t>(COLS));
	return resolution;
}

int lib_nCurses::getMaxY() const
{
	return COLS;
}

int lib_nCurses::getMaxX() const
{
	return LINES;
}
