/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <iostream>
#include <memory>
#include "../templates/DLLoader.hpp"
#include "core.hpp"

Core::Core(std::string name)
{
	for (unsigned it = 0; it < libsNames.size() && idx == UINT_MAX; it++)
		idx = libsNames[it] == name ? it : idx;
	if (idx == UINT_MAX)
		std::cerr << name + ": Invalid library name" << std::endl;
}

bool Core::start()
{
	bool ret = true;

	if (idx == UINT_MAX)
		ret = false;
	else {
		auto dlloader = DLLoader<IGraphicalLib>(libs[idx]);
		std::unique_ptr<IGraphicalLib> currentLib(dlloader.getInstance());
		std::cout << "Lib [" + currentLib->getName() + "] Loaded !"
			<< std::endl;
	}
	return ret;
}
