//
// Created by rectoria on 05/03/18.
//

#ifndef SFML_HPP
#define SFML_HPP

#include <string>
#include "IGraphicalLib.hpp"

class SFML : public IGraphicalLib {
public:
	SFML() = default;
	~SFML() = default;

public:
	void putPixel() final;
	const std::string &getName() const final;

private:
	std::string _name = "SFML";
};

#endif
