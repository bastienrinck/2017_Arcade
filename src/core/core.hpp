//
// Created by rectoria on 06/03/18.
//

#ifndef CORE_HPP
#define CORE_HPP

#include <string>
#include <vector>
#include <climits>
#include <memory>
#include "DLLoader.hpp"

class Core {
public:
	Core() = delete;
	explicit Core(std::string);
	~Core() = default;

public:
	bool start();
private:
	bool load_game(unsigned);
	bool load_lib();

	IGames *_currentGame;
	IGraphicalLib *_currentLib;
	std::vector<std::string> libsNames = {"nCurses", "SFML",
		"OpenGL"};
	std::vector<std::string> libs = {"lib_nCurses.so", "lib_SFML.so",
		"lib_OpenGL.so"};
	std::vector<std::string> gamesNames = {"Pacman"};
	std::vector<std::string> games = {"pacman.so"};
	unsigned _lidx = UINT_MAX;
};

#endif
