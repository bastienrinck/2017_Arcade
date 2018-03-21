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
	unsigned ret = 0;
	if (ac != 2) {
		std::cerr << "Wrong parameters" << std::endl;
		ret = 84;
	} else {
		try {
			Arcade::Core core(av[1]);
			if (!core.start())
				ret = 84;
		} catch (std::string &error){
			std::cerr << error;
			ret = 84;
		}
	}
	return ret;
}
