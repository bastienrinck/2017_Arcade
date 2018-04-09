/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <iostream>
#include "core/Core.hpp"

int main(int ac, char **av)
{
	int ret = 0;

	if (ac != 2){
		std::cerr << "Usage: " << av[0] + 2
			<< " [Graphical library name from ./lib]" << std::endl;
		ret = 84;
	}
	else {
		srand(static_cast<unsigned int>(time(nullptr)));
		Arcade::Core core(av[1]);
		if (core.getLibIdx() != UINT_MAX)
			core.start();
		else
			ret = 84;
	}
	return ret;
}
