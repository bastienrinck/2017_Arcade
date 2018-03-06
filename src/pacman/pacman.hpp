//
// Created by rectoria on 06/03/18.
//

#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "IGames.hpp"

class Pacman : public IGames{
public:
	Pacman() = default;
	~Pacman() = default;

public:
	const std::string &getName() const final;
private:
	std::string _name = "pacman";
};

extern "C" IGames *entryPoint(void){
	return  new Pacman();
}

#endif
