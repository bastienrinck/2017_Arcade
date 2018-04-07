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

std::string __game1("pacman");
std::string __game2("snake");

class PlayerStats
{
	public:
		PlayerStats();
		~PlayerStats();
	public:
		void AddGame(std::string Game);
		void GetGameStats(std::string Game, std::string PlayerName);
		std::string GetPlayerScore(std::string Game, std::string
		PlayerName);
		void PrintGame(std::string Game);
		void WriteStats(std::string Game);
		void AddScore(std::string PlayerName, std::string Score);
		void SetScore(std::string Game, std::string PlayerName,
			std::string Score);
private:
		std::map<std::string, std::map<std::string, std::string>> _Stats;
};

#endif //CPP_ARCADE_SCORE_HPP
