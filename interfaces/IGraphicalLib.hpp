//
// Created by rectoria on 05/03/18.
//

#ifndef IGRAPHICALLIB_HPP
#define IGRAPHICALLIB_HPP

class IGraphicalLib {
public :
	virtual ~ IGraphicalLib() = default;

public:
	virtual void putPixel() = 0;
	virtual const std::string &getName() const = 0;
};

#endif
