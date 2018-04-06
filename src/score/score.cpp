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

std::vector<std::string> read_file(std::string path)
{
	std::ifstream myfile(path);
	std::string line;
	std::regex reg("^(\\w+):(\\w*)$");
	std::smatch match;
	std::vector<std::string> result;

	//ouvre le dossier path et stoque après ':' dans result
	if (myfile) {
		while (getline(myfile, line)) {
				if (std::regex_match(line, match, reg)) {
					result.push_back(match[2]);
			}
		}
		myfile.close();
	} else
		std::cout << ERR_OPEN(path) << std::endl;

	//affiche le vecteur res
	for (int i = 0;i < result.size(); i++){
		std::cout << "ici: " << i << result[i] << std::endl;
	}
	return (result);
}

int main(int ac, char **av)
{
	read_file(".save/pacman.log");
	read_file(".save/snake.log");
	return 0;
}
