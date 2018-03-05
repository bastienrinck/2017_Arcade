/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <map>
#include <memory>
#include <iostream>
#include "IGraphicalLib.hpp"
#include "DLLoader/DLLoader.hpp"

int main(int ac, char **av)
{
	static std::map<std::string, DLLoader<IGraphicalLib> *> libs = {
		{"nCurses", new DLLoader<IGraphicalLib>("lib_nCurses.so")},
		{"SFML", new DLLoader<IGraphicalLib>("lib_SFML.so")},
		{"OpenGL", new DLLoader<IGraphicalLib>("lib_OpenGL.so")}};

	if (ac == 2 && libs.count(av[1])) {
		std::unique_ptr<IGraphicalLib> currentLib(
			libs[av[1]]->getInstance());
		std::cout << "Lib [" + currentLib->getName() + "] Loaded !"
			<< std::endl;
	} else if (ac == 2)
		std::cerr << "Invalid library name" << std::endl;
	else
		std::cerr << "Wrong parameters" << std::endl;
	return 0;
}
