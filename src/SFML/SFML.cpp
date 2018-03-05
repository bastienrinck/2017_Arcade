/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/
#include "SFML.hpp"

void SFML::putPixel()
{
}

const std::string &SFML::getName() const
{
	return _name;
}

extern "C" IGraphicalLib *entryPoint(void){
	return  new SFML();
}