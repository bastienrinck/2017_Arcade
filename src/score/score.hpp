/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**
*/

#ifndef CPP_ARCADE_SCORE_HPP
#define CPP_ARCADE_SCORE_HPP

#define SAVE_EXTENSION ".log"
#define SAVE_PATH "../.././.save/"
#define LIB_PATH "../.././lib/"
#define GAMES_PATH "../.././games/"

#define ERR_OPEN(path) "Error opening " + path

class PlayerStats
{
	public:
		PlayerStats();
		~PlayerStats();
	public:
		void AddGame(std::string Game);
		void GetGameStats(std::string Game, std::string PlayerName);
		void UpdatePlayerScore(std::string Game, std::string
		PlayerName, std::string Score);
		void PrintGame(std::string Game);
private:
		std::map<std::string, std::map<std::string, std::string>> _Stats;
};

#endif //CPP_ARCADE_SCORE_HPP
