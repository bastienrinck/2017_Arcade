/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**
*/

#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <iostream>
#include "score.hpp"

PlayerStats::PlayerStats()
{

}

PlayerStats::~PlayerStats()
{

}

/*std::string PlayerStats::GetPlayerScore(std::string Game,
					std::string PlayerName)
{
	for (int i = 0; i < _Stats.size(); i++) {
		std::cout << "player: " << _Stats[i] << std::endl;
		std::cout << "score: " <<  << std::endl; //debug
	}
	return _Stats;
}*/

void PlayerStats::AddGame(std::string Game)
{
	std::string path(SAVE_PATH + Game + SAVE_EXTENSION);
	std::ifstream myfile(path);
	std::string line;
	std::regex reg("^(\\w+):(\\w*)$");
	std::smatch match;

	//ouvre le dossier path et stoque après ':' dans _stats
	if (!myfile) {
		std::ofstream outfile(SAVE_PATH + Game + SAVE_EXTENSION);
		outfile.close();
	} else {
		while (getline(myfile, line)) {
			if (std::regex_match(line, match, reg)) {
				_Stats[Game][match[1].str()] = match[2].str();
			}
		}
		myfile.close();
	}
}

void PlayerStats::UpdatePlayerScore(std::string Game, std::string PlayerName,
				    std::string Score)
{
	std::string path(SAVE_PATH + Game + SAVE_EXTENSION);
	std::regex reg("^(\\w+):(\\w*)$");
	std::smatch match;
	std::map<std::string, std::string>::iterator i;

	for (i = _Stats[Game]
		.begin(); i != _Stats[Game].end(); i++) {
		std::cout << i->first << std::endl;
				if (i->first.compare(PlayerName) == 0) {
					std::cout << "joueur " << PlayerName
						  << " trouvé pour le jeu "
						  << Game << std::endl;
					break;
					}
	}
	if (i == _Stats[Game].end())
	std::cout << "joueur " << PlayerName << " non trouvé pour le jeu " <<  Game << std::endl;
}

int main(int ac, char **av)
{
	PlayerStats Stats;
	std::string Game("pacman");
	std::string PlayerName("Rinck");

	Stats.AddGame(Game);
	Stats.UpdatePlayerScore(Game, PlayerName, "499999");
	//read_file(".save/snake.log");
	return 0;
}
