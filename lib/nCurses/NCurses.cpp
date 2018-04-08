/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <ncurses.h>
#include <algorithm>
#include <iostream>
#include "NCurses.hpp"

Arcade::IGraphicLib *lib = nullptr;

__attribute__((constructor)) void init()
{
	lib = new Arcade::NCurses;
}

__attribute__((destructor)) void destruct()
{
	delete lib;
}

extern "C" Arcade::IGraphicLib *entryPoint(void)
{
	return lib;
}

Arcade::NCurses::~NCurses()
{
	endwin();
}

std::string Arcade::NCurses::getName() const
{
	return _name;
}

bool Arcade::NCurses::isOpen() const
{
	return _isOpen;
}

void Arcade::NCurses::closeRenderer()
{
	delwin(_win);
	endwin();
}

void Arcade::NCurses::openRenderer(std::string const &title)
{
	int h, w;

	(void)title;
	initscr();
	start_color();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, true);
	getmaxyx(stdscr, h, w);
	timeout(0);
	_win = newwin(h, w, 0, 0);
}

void Arcade::NCurses::clearWindow()
{
	wattron(_win, 0);
	wclear(_win);
}

void Arcade::NCurses::refreshWindow()
{
	wrefresh(_win);
}

int Arcade::NCurses::getPairIndex(int i, int j)
{
	std::pair<int, int> pair(i, j);
	auto iter = std::find(_pairedColor.begin(), _pairedColor.end(), pair);
	auto idx = static_cast<int>(_pairedColor.size() + 1);

	if (iter == _pairedColor.end()) {
		init_pair(static_cast<short>(idx), static_cast<short>(i),
			static_cast<short>(j));
		_pairedColor.push_back(pair);
	} else
		idx = static_cast<int>(iter - _pairedColor.begin() + 1);
	return idx;
}

int Arcade::NCurses::getColorIndex(Arcade::Color &color)
{
	auto raw = (unsigned char *)color;
	auto iter = std::find(_savedColor.begin(), _savedColor.end(), color);
	auto idx = static_cast<int>(_savedColor.size() + 1);

	if (iter == _savedColor.end()) {
		init_color(static_cast<short>(_savedColor.size() + 1),
			static_cast<short>(raw[0] * 3.92),
			static_cast<short>(raw[1] * 3.92),
			static_cast<short>(raw[2] * 3.92));
		_savedColor.emplace_back(color);
	} else
		idx = static_cast<int>(iter - _savedColor.begin() + 1);
	return idx;
}

void Arcade::NCurses::drawPixelBox(Arcade::PixelBox const &pB)
{
	for (size_t i = 0; i < pB.getHeight(); i++) {
		for (size_t j = 0; j < pB.getWidth(); j++) {
			auto pp = pB.getPixel(Arcade::Vect<size_t>(j, i));
			auto pairID = getPairIndex(getColorIndex(pp),
				getColorIndex(pp));
			wattron(_win, COLOR_PAIR(pairID));
			mvwprintw(_win, static_cast<int>(pB.getY() + i),
				static_cast<int>(pB.getX() + j), " ");
			wattroff(_win, COLOR_PAIR(pairID));
		}
	}
}

int Arcade::NCurses::getDoubleColorPair(Arcade::Color fg, Arcade::Color bg)
{
	auto fgColor = getColorIndex(fg);
	auto bgColor = getColorIndex(bg);

	return getPairIndex(fgColor, bgColor);
}

void Arcade::NCurses::drawText(Arcade::TextBox const &tB)
{
	auto pairID = getDoubleColorPair(tB.getColor(),
		tB.getBackgroundColor());

	wattron(_win, COLOR_PAIR(pairID));
	mvwprintw(_win, static_cast<int>(tB.getY()),
		static_cast<int>(tB.getX()), "%s", tB.getValue().c_str());
	wattroff(_win, COLOR_PAIR(pairID));
}

bool Arcade::NCurses::pollEvents()
{
	bool ret = false;
	int c;

	if ((c = getch()) != ERR) {
		if (_keyMap.count(c)){
			_events.push_back(_keyMap[c]);
			ret = true;
		}
	}

	return ret;
}

Arcade::Keys Arcade::NCurses::getLastEvent()
{
	Arcade::Keys key = Arcade::Keys::NONE;

	if (!_events.empty()) {
		key = _events.front();
		_events.pop_front();
	}
	return key;
}

void Arcade::NCurses::clearEvents()
{
	_events.clear();
}

Arcade::Vect<size_t> Arcade::NCurses::getScreenSize() const
{
	int x, y;

	getmaxyx(_win, y, x);
	return {static_cast<size_t>(x), static_cast<size_t>(y)};
}

size_t Arcade::NCurses::getMaxY() const
{
	return static_cast<size_t>(getmaxy(_win));
}

size_t Arcade::NCurses::getMaxX() const
{
	return static_cast<size_t>(getmaxx(_win));
}
