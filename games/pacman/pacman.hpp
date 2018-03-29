//
// Created by rectoria on 06/03/18.
//

#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "IGameLib.hpp"

class Pacman : public Arcade::IGameLib{
public:
	Pacman();
	~Pacman();

public:
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

	// Main loop of the game, called by a while in the core
	// Returns false if the game has to be ended
	bool loop(Arcade::IGraphicLib *graphicsLib) final;
private:
	std::string _name = "Pacman";
};

extern "C" Arcade::IGameLib *entryPoint(void){
	return  new Pacman();
}

#endif
