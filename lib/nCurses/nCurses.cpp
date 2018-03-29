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

std::string lib_nCurses::getName() const
{
	return _name;
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
	wclear(_win);
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

void lib_nCurses::drawPixelBox(Arcade::PixelBox &pB)
{
	for (size_t i = 0; i < pB.getHeight(); i++) {
		for (size_t j = 0; j < pB.getWidth(); j++) {
			Arcade::Vect<size_t> pos(j, i);
			auto pp = pB.getPixel(pos);
			start_color();
			init_color(1001, static_cast<short>(pp.getRed() * 3.9),
				static_cast<short>(pp.getGreen() * 3.9),
				static_cast<short>(pp.getBlue() * 3.9));
			attron(COLOR_PAIR(1001));
			mvwprintw(_win, static_cast<int>(pos.getY()),
				static_cast<int>(pos.getX()), " ");
			attroff(COLOR_PAIR(1001));
		}
	}
}

void lib_nCurses::drawText(Arcade::TextBox &tB)
{
	mvwprintw(_win, static_cast<int>(tB.getY()),
		static_cast<int>(tB.getX()), "%s", tB.getValue());
}

Arcade::Keys lib_nCurses::getLastEvent()
{
	//TODO LAST EVENT
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
