//
// Created by rectoria on 06/03/18.
//

#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "IGameLib.hpp"

namespace Arcade {
	class Pacman : public Arcade::IGameLib {
	public:
		Pacman() : _tB(_name, Arcade::Vect<size_t>(0, 0)) {};

		~Pacman() final = default;

	public:
		/* Get the name of the game */
		const std::string getName() const final;

		/* Resources handling */
		// Initializes the library
		bool init() final;

		// Unloads the library
		bool stop() final;

		// Processes the key obtained by the IGraphicLib from the user to update the game state
		bool applyEvent(Keys key) final;

		// Updates the game state. (Move the player forward and/or move the NPCs)
		bool update() final;

		// Renders the game state to the screen. This should call IGraphicLib::refresh() to display content to the user.
		void refresh(IGraphicLib &graphicLib) final;

		// To call at the end of the execution of the game (after the player loose or win) for getting his score
		size_t getScore() final;

	private:
		std::string _name = "Pacman";
		Arcade::TextBox _tB;
	};
}
#endif
