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
#include <sys/stat.h>

void PlayerStats::AddGame(std::string Game)
{
	std::string path(SAVE_PATH + Game + SAVE_EXTENSION);
	std::ifstream mydir(SAVE_PATH);
	std::ifstream myfile(path);
	std::string line;
	std::regex reg("^(\\w+):(\\w*)$");
	std::smatch match;

	//crée le dossier .save si il n'existe pas
	if (!mydir) {
		mkdir(SAVE_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	if (!myfile) {
		std::ofstream outfile(SAVE_PATH + Game + SAVE_EXTENSION);
		outfile.close();
	} else {
		//ouvre le dossier path et stoque après ':' dans _stats
		while (getline(myfile, line)) {
			if (std::regex_match(line, match, reg)) {
				_Stats[Game][match[1].str()] = match[2].str();
			}
		}
		myfile.close();
	}
}


/* Met à jour le highscore d'un joueur pour un jeu */
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
					i->second = Score;
					break;
					}
	}
	if (i == _Stats[Game].end())
	std::cout << "joueur " << PlayerName << " non trouvé pour le jeu " <<  Game << std::endl;
}

void PlayerStats::PrintGame(std::string Game)
{
	for (std::map<std::string, std::string>::iterator i = _Stats[Game].begin(); i != _Stats[Game].end(); i++)
		std::cout << "Highscore for player " << i->first << ": " <<
									 i->second << std::endl;
}

int main(int ac, char **av)
{
	PlayerStats Stats;
	std::string Game("pacman");
	std::string PlayerName("Rinck");

	Stats.AddGame(Game);
	Stats.UpdatePlayerScore(Game, PlayerName, "499999");
	Stats.PrintGame(Game);
	//read_file(".save/snake.log");
	return 0;
}
