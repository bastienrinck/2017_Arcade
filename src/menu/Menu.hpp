//
// Created by rectoria on 08/04/18.
//

#ifndef MENU_HPP
#define MENU_HPP

#include <map>
#include "DLLoader.hpp"
#include "../score/Score.hpp"
#include "IGameLib.hpp"
#include "IGraphicLib.hpp"

namespace Arcade {
	class Menu {
	public:
		Menu() = default;

		~Menu() = default;

		void setLists(std::vector<DLLoader<IGameLib> *> *,
		std::vector<DLLoader<IGraphicLib> *> *
		);
		void refresh(IGraphicLib *, unsigned, Arcade::Score);
		unsigned applyEvent(Keys);
		std::string getUserName() const;

	private:
		void printBackground(Arcade::IGraphicLib *,
			Arcade::Vect<size_t> &
		);
		void printGames(Arcade::IGraphicLib *, Arcade::Vect<size_t> &);
		void printLibs(Arcade::IGraphicLib *, Arcade::Vect<size_t> &,
			unsigned
		);
		void printScore(Arcade::IGraphicLib *, std::map<std::string, std::string>);

		std::vector<DLLoader<Arcade::IGameLib> *> *_games = nullptr;
		std::vector<DLLoader<Arcade::IGraphicLib> *> *_libs = nullptr;
		std::string _username = "player";
		unsigned _idx = 0;
		bool _score = false;
	};
}

#endif
