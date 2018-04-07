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

/* met le contenu de la map dans les fichiers .log à la destruction des objets */
void PlayerStats::WriteStats(std::string Game)
{
	std::string savepath(SAVE_PATH + Game + SAVE_EXTENSION);
	std::ofstream myfile(savepath);

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
		//ouvre le dossier path et stoque après ':' dans la map _stats
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

std::string PlayerStats::GetPlayerScore(std::string Game,
					std::string PlayerName)
{
	std::string path(SAVE_PATH + Game + SAVE_EXTENSION);
	std::map<std::string, std::string>::iterator i;

	for (i = _Stats[Game]
		.begin(); i != _Stats[Game].end(); i++) {
		std::cout << i->first << std::endl;
				/* le joueur a été trouvé dans le fichier de sauvegarde */
					if (i->first.compare(PlayerName) == 0) {
					std::cout << "joueur " << PlayerName
						  << " trouvé pour le jeu "
						  << Game << std::endl;
					break;
					}
	}
	/* joueur non existant */
	if (i == _Stats[Game].end()) {
		std::cout << "joueur " << PlayerName << " non trouvé pour le "
			"jeu " << Game << std::endl;
		return (""); /* pas d'autre idée pour ne pas toucher à _Stats[Game][PlayerName] */
	}
	return (_Stats[Game][PlayerName]);
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
	Stats.SetScore(Game, "James", "500");
	Stats.SetScore("Nibbler", "Miaous", "10");
	std::cout << "score: " << Stats.GetPlayerScore(Game, PlayerName) <<
								    std::endl;
	std::cout << "score: " << Stats.GetPlayerScore(Game, "James") <<
								    std::endl;
	std::cout << "score: " << Stats.GetPlayerScore(Game, "Jimmy") <<
		  std::endl;
	std::cout << "score: " << Stats.GetPlayerScore("Nibbler", "Jimmy") <<
		  std::endl;
	//Stats.PrintGame(Game);
	return 0;
}

// pour tester:
// g++ -std=c++11 score.cpp && ./a.out
// cat ../../.save/pacman.log (les fichiers .log sont à la racine dans le dossier .save)
