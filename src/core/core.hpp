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
#include "../score/score.hpp"

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

		std::vector<DLLoader<Arcade::IGameLib> *> *_games = nullptr;
		std::vector<DLLoader<Arcade::IGraphicLib> *> *_libs = nullptr;
		std::string _username = "player";
		unsigned _idx = 0;
	};

	class Core {
	public:
		explicit Core(std::string);

		~Core();

	public:
		bool start();
		size_t getLibIdx() const;

	private:
		template<typename T>
		bool loadLib(std::string &, std::string &,
			std::vector<DLLoader<T> *> &
		);

		template<typename T>
		bool inspectDirectory(std::string &&,
			std::vector<DLLoader<T> *> &
		);

		bool applyKeys(
			std::unordered_map<Arcade::Keys, bool (Core::*)()> &
		);

		void updateScore();
		bool prevLibG();
		bool nextLibG();
		bool prevGame();
		bool nextGame();
		bool restartGame();
		bool backMenu();
		bool exit();

		Menu _menu;
		Arcade::Score _score;
		std::vector<DLLoader<Arcade::IGraphicLib> *> _libs;
		std::vector<DLLoader<Arcade::IGameLib> *> _games;
		std::unordered_map<Arcade::Keys, bool (Core::*)()> _actions = {
			{Arcade::Keys::LEFT, &Core::prevLibG},
			{Arcade::Keys::RIGHT, &Core::nextLibG},
			{Arcade::Keys::DOWN, &Core::prevGame},
			{Arcade::Keys::UP, &Core::nextGame},
			{Arcade::Keys::SPACE, &Core::restartGame},
			{Arcade::Keys::BACKSPACE, &Core::backMenu},
			{Arcade::Keys::ESC, &Core::exit}};
		std::unordered_map<Arcade::Keys, bool (Core::*)()> _menuActions = {
			{Arcade::Keys::LEFT, &Core::prevLibG},
			{Arcade::Keys::RIGHT, &Core::nextLibG},
			{Arcade::Keys::ESC, &Core::exit}};
		unsigned _lidx = UINT_MAX;
		unsigned _gidx = UINT_MAX;
		bool _exit = false;
	};
}
#endif
