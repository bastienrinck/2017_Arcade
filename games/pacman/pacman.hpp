//
// Created by rectoria on 06/03/18.
//

#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "IGameModule.hpp"

class Pacman : public Arcade::IGameModule{
public:
	/* Get the name of the game */
	std::string getName() final;

	/* Resource Handling */
	// Initializes the Graphics library for this game
	void loadRessource(Arcade::IGraphicLib *graphicsLib) final;

	// Unloads the Graphics library for this game
	void freeRessource(Arcade::IGraphicLib *graphicsLib) final;


	/* Rendering functions */
	// Updates the game state according to the player inputs
	void update(Arcade::IGraphicLib *graphicsLib) final;

	// Renders the game state to the screen
	void render(Arcade::IGraphicLib *graphicsLib) final;
private:
	std::string _name = "pacman";
};

extern "C" Arcade::IGameModule *entryPoint(void){
	return  new Pacman();
}

#endif
