//
// Created by rectoria on 30/03/18.
//

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <IGameLib.hpp>
#include <list>

namespace Arcade {
	class snake : public IGameLib {
	public:
		snake() = default;
		~snake() final = default;

		/* Get the name of the game */
		const std::string &getName() const final;


		/* Resources handling */
		// Initializes the library
		bool init() final;

		// Unloads the library
		bool stop() final;

		// Closes the game => stop loop (go menu)
		bool close() final;

		// Opens the game => start loop
		bool open() final;

		// Processes the key obtained by the IGraphicLib from the user to update the game state
		void applyEvent(Keys key) final;

		// Updates the game state. (Move the player forward and/or move the NPCs)
		void update() final;

		// Renders the game state to the screen. This should call IGraphicLib::refresh() to display content to the user.
		void refresh(IGraphicLib *graphicLib) final;

	private:
		bool moveUp();
		bool moveDown();
		bool moveLeft();
		bool moveRight();
		void print_background(IGraphicLib *);

		const std::string _name = "snake";
		std::list<Arcade::Vect<size_t>> _snake;
		std::vector<char> _map;
		size_t _height = 40;
		size_t _width = 70;
		size_t _direction = 2;
	};
};


#endif
