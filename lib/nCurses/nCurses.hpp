//
// Created by rectoria on 05/03/18.
//

#ifndef NCURSES_HPP
#define NCURSES_HPP

#include <string>
#include <list>
#include <unordered_map>
#include "IGraphicLib.hpp"

namespace Arcade {

	class nCurses : public Arcade::IGraphicLib {
	public:
		nCurses() = default;

		~nCurses() final;

	public:

		/* Get the name of the library */
		std::string getName() const final;

		/* Window handling */
		// Main loop condition
		bool isOpen() const final;

		// Closes the window => stop loop (go menu)
		void closeRenderer() final;

		// Opens the window => start loop
		void openRenderer(std::string const &) final;

		// Clears the screen
		void clearWindow() final;

		// Displays the buffered frame to the screen
		void refreshWindow() final;

		/* Rendering functions */
		// Draws a PixelBox or the sprite if supported
		void drawPixelBox(PixelBox const &) final;

		// Draws a TextBox
		void drawText(TextBox const &) final;

		/* EVENT HANDLING */
		/* */
		/* This part can seem complicated but the implementation is quite simple. */
		/* */
		/* pollEvent() fetches the events from the user and saves it */
		/* inside an std::vector<Arcade::Keys> or std::list<Arcade::Keys>. */
		/* It returns true if at least one new event was added to the list, false otherwise. */
		/* */
		/* getLastEvent() returns the first event of the list. (using front() and pop_front() methods) */
		/* or Arcade::Keys::NONE if the list is empty. */
		/* */
		/* clearEvents() clears the list (using clear() method). */
		/* */
		bool pollEvents() final;
		Keys getLastEvent() final;
		void clearEvents() final;

		/* Context Info */
		// get the X and Y max of the windows
		Vect<size_t> getScreenSize() const final;

		// get the Y max of the windows
		size_t getMaxY() const final;

		// get the X max of the windows
		size_t getMaxX() const final;

	private:
		int getColorIndex(Arcade::Color &);
		int getPairIndex(int, int);
		int getDoubleColorPair(Color, Color);

		std::string _name = "nCurses";
		std::list<Arcade::Keys> _events;
		WINDOW *_win = nullptr;
		bool _isOpen = false;
		std::vector<Arcade::Color> _savedColor;
		std::vector<std::pair<int, int>> _pairedColor;
		std::unordered_map<int, Arcade::Keys> _keyMap = {
			{'a', Arcade::Keys::A}, {'b', Arcade::Keys::B},
			{'c', Arcade::Keys::C}, {'d', Arcade::Keys::D},
			{'e', Arcade::Keys::E}, {'f', Arcade::Keys::F},
			{'g', Arcade::Keys::G}, {'h', Arcade::Keys::H},
			{'i', Arcade::Keys::I}, {'j', Arcade::Keys::J},
			{'k', Arcade::Keys::K}, {'l', Arcade::Keys::L},
			{'m', Arcade::Keys::M}, {'n', Arcade::Keys::N},
			{'o', Arcade::Keys::O}, {'p', Arcade::Keys::P},
			{'q', Arcade::Keys::Q}, {'r', Arcade::Keys::R},
			{'s', Arcade::Keys::S}, {'t', Arcade::Keys::T},
			{'u', Arcade::Keys::U}, {'v', Arcade::Keys::V},
			{'w', Arcade::Keys::W}, {'x', Arcade::Keys::X},
			{'y', Arcade::Keys::Y}, {'z', Arcade::Keys::Z},
			{KEY_LEFT, Arcade::Keys::LEFT},
			{KEY_RIGHT, Arcade::Keys::RIGHT},
			{KEY_UP, Arcade::Keys::UP},
			{KEY_DOWN, Arcade::Keys::DOWN},
			{KEY_ENTER, Arcade::Keys::ENTER},
			{' ', Arcade::Keys::SPACE},
			{KEY_DC, Arcade::Keys::DELETE},
			{KEY_BACKSPACE, Arcade::Keys::BACKSPACE},
			{'\t', Arcade::Keys::TAB}, {27, Arcade::Keys::ESC}};
	};
};
#endif
