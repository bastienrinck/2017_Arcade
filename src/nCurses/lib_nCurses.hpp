//
// Created by rectoria on 05/03/18.
//

#ifndef NCURSES_HPP
#define NCURSES_HPP

#include <string>
#include "IGraphicalLib.hpp"

class lib_nCurses : public IGraphicalLib {
public:
	lib_nCurses() = default;
	~lib_nCurses() = default;

public:
	void putPixel() final;
	const std::string &getName() const final;

private:
	std::string _name = "lib_nCurses";
};

#endif
