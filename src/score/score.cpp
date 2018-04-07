/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**
*/

#include <sys/stat.h>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <iostream>
#include "score.hpp"

PlayerStats::PlayerStats()
{
	std::ifstream mydir(SAVE_PATH);

	/* crée le dossier .save si il n'existe pas */
	if (!mydir)
		mkdir(SAVE_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

PlayerStats::~PlayerStats()
{
	WriteStats(__game1);
	WriteStats(__game2);
}

void PlayerStats::WriteStats(std::string Game)
{
	std::cout << "in writestat fc" << std::endl;

	std::string savepathpacman(SAVE_PATH + Game + SAVE_EXTENSION);
	std::ofstream myfile(savepathpacman);

	for (std::map<std::string, std::string>::iterator i = _Stats[Game].begin(); i != _Stats[Game].end(); i++) {
		myfile << i->first << ":" << i->second << std::endl;
	}
	myfile.close();
}

//
/*	for (i = _Stats[Game].begin(); i != _Stats[Game].end(); i++)
		for (i = _Stats[Game].begin(); i != _Stats[Game].end(); i++);*/


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

/*void PlayerStats::AddScore(std::string PlayerName, std::string Score)
{
	std::cout << "dans la fonction addscore" << std::endl;
}*/

void PlayerStats::SetScore(std::string Game, std::string
PlayerName, std::string Score)
{
	_Stats[Game][PlayerName] = Score;
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
				/* le joueur a été trouvé dans le fichier de sauvegarde */
					if (i->first.compare(PlayerName) == 0) {
					std::cout << "joueur " << PlayerName
						  << " trouvé pour le jeu "
						  << Game << std::endl;
					i->second = Score;
					break;
					}
	}
	/* joueur non existant */
	if (i == _Stats[Game].end()) {
		_Stats[Game][PlayerName] = Score;
	}
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
	Stats.SetScore(Game, PlayerName, "48");
	Stats.UpdatePlayerScore(Game, PlayerName, "499999");
	//Stats.PrintGame(Game);
	return 0;
}

// pour tester:
// g++ -std=c++11 score.cpp && ./a.out
// cat ../../.save/pacman.log
