/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#ifndef DLLOADER_HPP
#define DLLOADER_HPP

#include <string>
#include <dlfcn.h>
#include "IGraphicalLib.hpp"

template<typename T>
class DLLoader {
public :

	DLLoader() = delete;
	explicit DLLoader(std::string &&);

	~DLLoader();


	T *getInstance();

private:
	void *ptr;
	std::string _filePath;
	std::string _fctName = "entryPoint";
};

#endif
