//
// Created by rectoria on 06/03/18.
//

#ifndef CORE_HPP
#define CORE_HPP

#include <string>
#include <climits>
#include <memory>
#include <vector>
#include "DLLoader.hpp"

namespace Arcade {
	class Core {
	public:
		explicit Core(std::string);

		~Core();

	public:
		bool start();

	private:
		bool inspectDirectory(std::string &&,
			std::vector<std::string> &
		);

		bool loadGame();

		bool loadLib();

		DLLoader<Arcade::IGameLib> *_currentGame = nullptr;
		DLLoader<Arcade::IGraphicLib> *_currentLib = nullptr;
		std::vector<std::string> _libs;
		std::vector<std::string> _games;
		unsigned _lidx = UINT_MAX;
		unsigned _gidx = 0;
	};
}
#endif
