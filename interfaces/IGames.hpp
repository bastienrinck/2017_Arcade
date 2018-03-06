//
// Created by rectoria on 06/03/18.
//

#ifndef IGAMES_HPP
#define IGAMES_HPP

class IGames {
public:
	virtual ~IGames() = default;

public:
	virtual const std::string &getName() const = 0;
};

#endif
