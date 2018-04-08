//
// Created by rectoria on 03/04/18.
//

#ifndef SDL2_HPP
#define SDL2_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <list>
#include "IGraphicLib.hpp"

namespace Arcade {
	class Sdl : public IGraphicLib {
	public:
		Sdl();
		~Sdl() final;

		/* Get the name of the library */
		std::string getName() const final;

		/* Window handling */
		// Main loop condition
		bool isOpen() const final;

		// Closes the window => stop loop (go menu)
		void closeRenderer() final;

		// Opens the window => start loop
		void openRenderer(std::string const &title) final;

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
		std::string _name = "SDL2";
		SDL_Window *_window = nullptr;
		SDL_Renderer *_renderer = nullptr;
		SDL_Texture *_texture = nullptr;
		TTF_Font *_font = nullptr;
		SDL_Texture *_text = nullptr;
		std::list<Arcade::Keys> _events;
		std::unordered_map<SDL_Keycode, Arcade::Keys> _keyMap = {
			{SDLK_a, Arcade::Keys::A},
			{SDLK_b, Arcade::Keys::B},
			{SDLK_c, Arcade::Keys::C},
			{SDLK_d, Arcade::Keys::D},
			{SDLK_e, Arcade::Keys::E},
			{SDLK_f, Arcade::Keys::F},
			{SDLK_g, Arcade::Keys::G},
			{SDLK_h, Arcade::Keys::H},
			{SDLK_i, Arcade::Keys::I},
			{SDLK_j, Arcade::Keys::J},
			{SDLK_k, Arcade::Keys::K},
			{SDLK_l, Arcade::Keys::L},
			{SDLK_m, Arcade::Keys::M},
			{SDLK_n, Arcade::Keys::N},
			{SDLK_o, Arcade::Keys::O},
			{SDLK_p, Arcade::Keys::P},
			{SDLK_q, Arcade::Keys::Q},
			{SDLK_r, Arcade::Keys::R},
			{SDLK_s, Arcade::Keys::S},
			{SDLK_t, Arcade::Keys::T},
			{SDLK_u, Arcade::Keys::U},
			{SDLK_v, Arcade::Keys::V},
			{SDLK_w, Arcade::Keys::W},
			{SDLK_x, Arcade::Keys::X},
			{SDLK_y, Arcade::Keys::Y},
			{SDLK_z, Arcade::Keys::Z},
			{SDLK_LEFT, Arcade::Keys::LEFT},
			{SDLK_RIGHT, Arcade::Keys::RIGHT},
			{SDLK_UP, Arcade::Keys::UP},
			{SDLK_DOWN, Arcade::Keys::DOWN},
			{SDLK_RETURN, Arcade::Keys::ENTER},
			{SDLK_SPACE, Arcade::Keys::SPACE},
			{SDLK_DELETE, Arcade::Keys::DELETE},
			{SDLK_BACKSPACE, Arcade::Keys::BACKSPACE},
			{SDLK_TAB, Arcade::Keys::TAB},
			{SDLK_ESCAPE, Arcade::Keys::ESC}};
	};
};


#endif
