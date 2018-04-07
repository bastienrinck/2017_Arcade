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
#include <iostream>
#include "IGameLib.hpp"
#include "IGraphicLib.hpp"

template<typename T>
class DLLoader {
public :

	DLLoader() = delete;

	explicit DLLoader(std::string &filepath, std::string &folder)
		: _filePath(folder + filepath)
	{
		void *temp = nullptr;

		if (!(ptr = dlopen(_filePath.c_str(), RTLD_LAZY))) {
			std::cerr << "Error while loading " << filepath
				<< std::endl;
			std::cerr << dlerror() << std::endl;
		} else if (!(temp = dlsym(ptr, _fctName.c_str()))) {
			std::cerr << "Error while loading " << filepath
				<< std::endl;
			std::cerr << "Reason: " << dlerror() << std::endl;
		} else
			_instance = reinterpret_cast<T *(*)()>(temp)();
		_filePath = folder + "./" + filepath;
	}

	~DLLoader()
	{
		if (ptr)
			dlclose(ptr);
	}

public:
	T *getInstance()
	{
		return _instance;
	};

	std::string getFilePath() const
	{
		return _filePath;
	}

private:
	void *ptr;
	T *_instance = nullptr;
	std::string _filePath;
	std::string _fctName = "entryPoint";
};

#endif
