//
// Created by rectoria on 06/03/18.
//

#ifndef CORE_HPP
#define CORE_HPP

#include <string>
#include <vector>
#include <climits>

class Core {
public:
	Core() = delete;
	explicit Core(std::string);
	~Core() = default;

public:
	bool start();
private:
	std::vector<std::string> libsNames = {"nCurses", "SFML",
		"OpenGL"};
	std::vector<std::string> libs = {"lib_nCurses.so", "lib_SFML.so",
		"lib_OpenGL.so"};
	unsigned idx = UINT_MAX;
};

#endif
