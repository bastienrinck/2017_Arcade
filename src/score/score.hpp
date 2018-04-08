/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**
*/

#ifndef SCORE_HPP
#define SCORE_HPP

#define SAVE_EXTENSION ".log"
#define SAVE_PATH "./.save/"

namespace Arcade{
	class Score
	{
	public:
		Score();
		~Score();
	public:
		void addGame(std::string &);
		std::map<std::string, std::string> getGameStats(std::string &);
		int getPlayerScore(std::string &, std::string &);
		void writeStats(std::string);
		void setScore(std::string &, std::string &, unsigned);
	private:
		std::map<std::string, std::map<std::string, std::string>> _stats;
	};
}

#endif
