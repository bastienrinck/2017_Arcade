/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <iostream>
#include "core/core.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		std::cerr << "Wrong parameters" << std::endl;
	else {
		srand(time(NULL));
		Arcade::Core core(av[1]);
		if (core.getLibIdx() != UINT_MAX)
			core.start();
	}
	return 0;
}
