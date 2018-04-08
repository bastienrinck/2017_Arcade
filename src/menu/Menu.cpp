/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/
#include <climits>
#include "Menu.hpp"

void Arcade::Menu::printBackground(Arcade::IGraphicLib *gl,
	Arcade::Vect<size_t> &mode
)
{
	auto background = Arcade::PixelBox(mode, Arcade::Vect<size_t>(0, 0),
		Arcade::Color(0, 0, 0, 255));
	auto backgroundMenu = Arcade::PixelBox(
		Arcade::Vect<size_t>(mode.getX() / 10 * 4,
			mode.getY() / 5 * 4));

	gl->drawPixelBox(background);
	backgroundMenu.setX(mode.getX() / 20);
	backgroundMenu.setY(mode.getY() / 20);
	gl->drawPixelBox(backgroundMenu);
	backgroundMenu.setX(mode.getX() / 20 + mode.getX() / 2);
	gl->drawPixelBox(backgroundMenu);
}

void Arcade::Menu::printGames(Arcade::IGraphicLib *gl,
	Arcade::Vect<size_t> &mode
)
{
	auto select = Arcade::Color(128, 0, 0, 255);
	auto other = Arcade::Color(0, 0, 0, 255);
	auto text = Arcade::TextBox("", Arcade::Vect<size_t>(0, 0));

	text.setBackgroundColor(Arcade::Color(221, 221, 221, 255));
	for (unsigned i = 0; i < _games->size(); ++i) {
		text.setValue((*_games)[i]->getInstance()->getName());
		text.setY(static_cast<size_t>(
			mode.getY() * 0.1 +
				(i * (_games->size() * mode.getY() * 0.04))));
		text.setX(mode.getX() / 10);
		text.setColor(_idx == i ? select : other);
		gl->drawText(text);
	}
}

void Arcade::Menu::printLibs(Arcade::IGraphicLib *gl,
	Arcade::Vect<size_t> &mode, unsigned idx
)
{
	auto select = Arcade::Color(128, 0, 0, 255);
	auto other = Arcade::Color(0, 0, 0, 255);
	auto text = Arcade::TextBox("", Arcade::Vect<size_t>(0, 0));

	text.setBackgroundColor(Arcade::Color(221, 221, 221, 255));
	for (unsigned i = 0; i < _libs->size(); ++i) {
		text.setValue((*_libs)[i]->getInstance()->getName());
		text.setY(static_cast<size_t>(
			mode.getY() * 0.1 +
				(i * (_libs->size() * mode.getY() * 0.04))));
		text.setColor(idx == i ? select : other);
		text.setX(mode.getX() / 10 + mode.getX() / 2);
		gl->drawText(text);
	}
}

void Arcade::Menu::printScore(Arcade::IGraphicLib *gl,
	std::map<std::string, std::string> scores
)
{
	auto mode = gl->getScreenSize();
	auto text = Arcade::TextBox("", Arcade::Vect<size_t>(0, 0));
	int i = 0;

	text.setColor(Arcade::Color(0, 0, 0, 255));
	text.setBackgroundColor(Arcade::Color(221, 221, 221, 255));
	for (auto &cell : scores) {
		text.setX(mode.getX() / 10 + mode.getX() / 2);
		text.setY(static_cast<size_t>(mode.getY() * 0.1 +
			(i * (scores.size() * mode.getY() * 0.04))));
		text.setValue(cell.first + ": " + cell.second);
		gl->drawText(text);
		i++;
	}
}

void Arcade::Menu::refresh(Arcade::IGraphicLib *gl, unsigned idx,
	Arcade::Score score
)
{
	auto mode = gl->getScreenSize();
	auto gameName = (*_games)[_idx]->getInstance()->getName();
	auto text = Arcade::TextBox("Gamer tag : " + _username,
		Arcade::Vect<size_t>(0, 0));

	gl->clearWindow();
	printBackground(gl, mode);
	gl->drawText(text);
	printGames(gl, mode);
	if (_score)
		printScore(gl, score.getGameStats(gameName));
	else
		printLibs(gl, mode, idx);
	text.setColor(Arcade::Color(0, 255, 0, 255));
	gl->refreshWindow();
}

unsigned Arcade::Menu::applyEvent(Arcade::Keys key)
{
	const char keysC[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
		'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z'};

	if (key == Arcade::Keys::DOWN && _idx < _games->size() - 1)
		_idx += 1;
	else if (key == Arcade::Keys::UP && _idx > 0)
		_idx -= 1;
	else if (key == Arcade::Keys::TAB)
		_score = !_score;
	else if (key < 26)
		_username += keysC[key - 1];
	else if (key == Arcade::Keys::BACKSPACE && !_username.empty())
		_username.pop_back();
	return (key == Arcade::Keys::ENTER) ? _idx : UINT_MAX;
}

void Arcade::Menu::setLists(std::vector<DLLoader<Arcade::IGameLib> *> *games,
	std::vector<DLLoader<Arcade::IGraphicLib> *> *libs
)
{
	_games = games;
	_libs = libs;
}

std::string Arcade::Menu::getUserName() const
{
	return _username;
}