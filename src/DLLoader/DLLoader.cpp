/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <iostream>
#include "DLLoader.hpp"

template<typename T>
DLLoader<T>::DLLoader(std::string &&filepath) : _filePath("./lib/" + filepath)
{
	ptr = dlopen(_filePath.c_str(), RTLD_LAZY);
	if (!ptr)
		std::cerr << dlerror() << std::endl;
}

template<typename T>
DLLoader<T>::~DLLoader()
{
	if (ptr)
		dlclose(ptr);
}

template<typename T>
T *DLLoader<T>::getInstance()
{
	void *temp = nullptr;

	if(ptr)
		temp = dlsym(ptr, _fctName.c_str());
	return reinterpret_cast<T *(*)()>(temp)();
};