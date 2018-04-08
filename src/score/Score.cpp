/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**
*/

#include <sys/stat.h>
#include <fstream>
#include <regex>
#include <iostream>
#include "Score.hpp"

Arcade::Score::Score()
{
	std::ifstream mydir(SAVE_PATH);

	/* crée le dossier .save si il n'existe pas */
	if (!mydir)
		mkdir(SAVE_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

Arcade::Score::~Score()
{
	for (auto &cell : _stats)
		if (!cell.second.empty())
			writeStats(cell.first);
}

/* met le contenu de la map dans les fichiers .log à la destruction des objets */
void Arcade::Score::writeStats(std::string game)
{
	std::string savepath(SAVE_PATH + game + SAVE_EXTENSION);
	std::ofstream myfile(savepath);

	for (auto &cell : _stats[game])
		myfile << cell.first << ":" << cell.second << std::endl;
	myfile.close();
}

int Arcade::Score::getPlayerScore(std::string &game, std::string &pName)
{
	if (_stats[game].find(pName) != _stats[game].end())
		return std::stoi(_stats[game][pName]);
	return 0;
}

void Arcade::Score::addGame(std::string &game)
{
	std::string path(SAVE_PATH + game + SAVE_EXTENSION);
	std::ifstream myfile(path);
	std::string line;
	std::regex reg("^(\\w+):(\\w*)$");
	std::smatch match;

	if (!myfile) {
		std::ofstream outfile(SAVE_PATH + game + SAVE_EXTENSION);
		outfile.close();
	} else {
		//ouvre le dossier path et stoque après ':' dans la map _stats
		while (getline(myfile, line)) {
			if (std::regex_match(line, match, reg)) {
				_stats[game][match[1].str()] = match[2].str();
			}
		}
		myfile.close();
	}
}

void Arcade::Score::setScore(std::string &game, std::string &pName,
	unsigned score
)
{
	_stats[game][pName] = std::to_string(score);
}

std::map<std::string, std::string> Arcade::Score::getGameStats(std::string &game)
{
	return _stats[game];
}