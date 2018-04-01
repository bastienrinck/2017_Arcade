//
// Created by rectoria on 06/03/18.
//

#ifndef CORE_HPP
#define CORE_HPP

#include <string>
#include <climits>
#include <memory>
#include <vector>
#include <regex>
#include <dirent.h>
#include <unordered_map>
#include "DLLoader.hpp"

namespace Arcade {
	class Menu {
	public:
		Menu() = default;
		~Menu() = default;

		void setList(std::vector<DLLoader<Arcade::IGameLib> *> *);
		void refresh(IGraphicLib *);
		unsigned applyEvent(Keys);

	private:

		std::vector<DLLoader<Arcade::IGameLib> *> *_list = nullptr;
		unsigned _idx = 0;
	};

	class Core {
	public:
		explicit Core(std::string);
		~Core();

	public:
		bool start();

	private:
		template<typename T>
		bool loadLib(std::string &, std::string &, std::vector<DLLoader<T> *> &);

		template<typename T>
		bool inspectDirectory(std::string &&, std::vector<DLLoader<T> *> &);

		bool applyKeys(std::unordered_map<Arcade::Keys, bool (Core::*)()> &);

		bool prevLibG();

		bool nextLibG();

		bool prevGame();

		bool nextGame();

		bool restartGame();

		bool backMenu();

		bool exit();

		Menu _menu;
		std::vector<DLLoader<Arcade::IGraphicLib> *> _libs;
		std::vector<DLLoader<Arcade::IGameLib> *> _games;
		unsigned _lidx = UINT_MAX;
		unsigned _gidx = UINT_MAX;
	};
}
#endif
