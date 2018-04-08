/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "Pacman.hpp"

Arcade::IGameLib *lib = nullptr;

__attribute__((constructor)) void init()
{
	lib = new Arcade::Pacman;
}

__attribute__((destructor)) void destruct()
{
	delete lib;
}

extern "C" Arcade::IGameLib *entryPoint(void)
{
	return lib;
}

Arcade::Pacman::Pacman()
{
	_startTime = static_cast<size_t>(time(nullptr));
}

bool Arcade::Pacman::init()
{
	// Initialisation des variables, des Fantom et de la map
	loadMap();
	initPosition();
	countFood();
	return true;
}


void Arcade::Pacman::clearValue()
{
	// Remet à 0 les valeurs
	_score = 0;
	_time = 0;
	_startTime = static_cast<size_t>(time(nullptr));
	_posp.pop_back();
	_posp.pop_back();

	_posf.pop_back();
	_posf.pop_back();
	_posf.pop_back();
	_posf.pop_back();
}

void Arcade::Pacman::initPosition()
{
	// Initialisation de toutes les positions
	_posp.push_back(27 - 1); // x
	_posp.push_back(30 - 1); // y

	std::vector<size_t> one = {13 - 1 , 14 - 1, 0, 32};
	_posf.push_back(one);

	std::vector<size_t> two =  {13 - 1 , 15 - 1, 0, 32};
	_posf.push_back(two);

	std::vector<size_t> three = {15 - 1 , 15 - 1, 0, 32};
	_posf.push_back(three);

	std::vector<size_t> four = {15 - 1 , 14 - 1, 0, 32};
	_posf.push_back(four);
}

bool Arcade::Pacman::stop()
{
	// Lorsque BACKSPACE est cliqué
	clearValue();
	init();
	return true;
}

bool Arcade::Pacman::applyEvent(Arcade::Keys key)
{
	std::unordered_map<Arcade::Keys, size_t> action = {{Arcade::Keys::Z, 0},
		{Arcade::Keys::S, 1}, {Arcade::Keys::Q, 2},
		{Arcade::Keys::D, 3}};
	bool (Arcade::Pacman::*moveArr[4])() = {&Arcade::Pacman::moveUpP,
		&Arcade::Pacman::moveDownP, &Arcade::Pacman::moveLeftP,
		&Arcade::Pacman::moveRightP};

	if (action.count(key))
		return (this->*moveArr[action.at(key)])();
	return true;
}

bool Arcade::Pacman::update()
{
	goToHouse();
	return end_condition();
}

void Arcade::Pacman::refresh(IGraphicLib& gl)
{
	// Gestion du temsp de jeu
	_time = time(nullptr) - _startTime;

	// Movement du Pacman et des Fantoms
	movePacman();
	moveFantom();

	// Condition de win (avoir tout mangé sur la map)
	if (_food <= 0) {
		clearValue();
		init();
	}

	auto res = gl.getScreenSize();
	auto pWidth = static_cast<size_t>(res.getX() * 0.6 / _width);
	auto pHeight = static_cast<size_t>(res.getY() * 0.6 / _height);
	auto offsetX = static_cast<size_t>(res.getX() *0.3);
	auto offsetY = static_cast<size_t>(res.getY() *0.3);
	Arcade::TextBox score = Arcade::TextBox("Score : " + std::to_string(static_cast<unsigned >(_score)), Arcade::Vect<size_t>());
	Arcade::TextBox timer = Arcade::TextBox("Time : " + std::to_string(static_cast<unsigned >(_time)), Arcade::Vect<size_t>(res.getX() / 2, 0));
	Arcade::PixelBox pB;

	gl.clearWindow();

	//Print du score et du timer
	gl.drawText(score);
	gl.drawText(timer);

	//Print du labyrinthe
	for (unsigned i = 0; i < _map.size(); ++i){
		if (_map[i] == '=')
			pB = Arcade::PixelBox(Arcade::Vect<size_t>(pWidth, pHeight), Arcade::Vect<size_t>(), Arcade::Color(64, 25, 76, 255));
		else if (_map[i] == '.')
			pB = Arcade::PixelBox(Arcade::Vect<size_t>(pWidth, pHeight), Arcade::Vect<size_t>(), Arcade::Color(183, 110, 0, 255));
		else
			pB = Arcade::PixelBox(Arcade::Vect<size_t>(pWidth, pHeight), Arcade::Vect<size_t>(), Arcade::Color(236, 117, 115, 255));
		if (_map[i] == '=' || _map[i] == '.' || _map[i] == 'o'){
			pB.setX(offsetX + i % (_width) * pWidth);
			pB.setY(offsetY + i / (_width) * pHeight);
			gl.drawPixelBox(pB);
		}
	}

	//Print du Pacman
	pB = Arcade::PixelBox(Arcade::Vect<size_t>(pWidth, pHeight), Arcade::Vect<size_t>(), Arcade::Color(253, 255, 0, 255));
	pB.setX(offsetX + _posp[0] * pWidth);
	pB.setY(offsetY + _posp[1] * pHeight);
	gl.drawPixelBox(pB);


	//Print des fantomes
	//F1
	pB = Arcade::PixelBox(Arcade::Vect<size_t>(pWidth, pHeight), Arcade::Vect<size_t>(), Arcade::Color(234, 130, 229, 255));
	pB.setX(offsetX + _posf[0][0] * pWidth);
	pB.setY(offsetY + _posf[0][1] * pHeight);
	gl.drawPixelBox(pB);

	//F2
	pB = Arcade::PixelBox(Arcade::Vect<size_t>(pWidth, pHeight), Arcade::Vect<size_t>(), Arcade::Color(70, 191, 238, 255));
	pB.setX(offsetX + _posf[1][0] * pWidth);
	pB.setY(offsetY + _posf[1][1] * pHeight);
	gl.drawPixelBox(pB);

	//F3
	pB = Arcade::PixelBox(Arcade::Vect<size_t>(pWidth, pHeight), Arcade::Vect<size_t>(), Arcade::Color(208, 62, 25, 255));
	pB.setX(offsetX + _posf[2][0] * pWidth);
	pB.setY(offsetY + _posf[2][1] * pHeight);
	gl.drawPixelBox(pB);

	//F4
	pB = Arcade::PixelBox(Arcade::Vect<size_t>(pWidth, pHeight), Arcade::Vect<size_t>(), Arcade::Color(219, 133, 28, 255));
	pB.setX(offsetX + _posf[3][0] * pWidth);
	pB.setY(offsetY + _posf[3][1] * pHeight);
	gl.drawPixelBox(pB);

	gl.refreshWindow();
}

bool Arcade::Pacman::end_condition()
{
	// Gestion du temps de GodMod
	if (_time - _timeGod >= 10)
		_god = false;

	// Condition de fin (si un fantom attrape Pacman)
	for (int i = 0; i != 4 ; i++) {
		if (_posf[i][0] == _posp[0]
		    && _posf[i][1] == _posp[1] && !_god) {
			// Réinitialisation des variables
			clearValue();
			_score = 0;
			init();
			return false;
		}
	}
	return true;
}

void Arcade::Pacman::goToHouse()
{
	// Réinitialise la position d'un fantom si il est mangé
	for (int i = 0 ; i != 4 ; i++) {
		if (_posp[0] == _posf[i][0] && _posp[1] == _posf[i][1]
			&& _god) {
			switch (i) {
				case 0:
					setValue(12, 13, 0, 32, i);
					break;
				case 1:
					setValue(12, 14, 0, 32, i);
					break;
				case 2:
					setValue(14, 14, 0, 32, i);
					break;
				case 3:
					setValue(14, 13, 0, 32, i);
					break;
			}
		}
	}
}

void Arcade::Pacman::setValue(size_t x, size_t y, size_t pos,
	size_t old_char, int nb)
{
	// Set la position d'un fantom
	_posf[nb][0] = x;
	_posf[nb][1] = y;
	_posf[nb][2] = pos;
	_posf[nb][3] = old_char;
}

void Arcade::Pacman::loadMap()
{
	// Chargement de la map dans le fichier map.txt
	std::ifstream input("map.txt");
	char tmp;

	if (!input) {
		std::cout << "Error : file 'map.txt' not found. The default "
	       "map is loaded" << std::endl;
		_map = _defaultMap;
	} else {
		while (input.read(&tmp, 1)) {
			if (tmp != '\n')
				_map.push_back(tmp);
		}
	}
}

/*
**  Movement
*/

// PACMAN

bool Arcade::Pacman::moveUpP() // dir = 1
{
	// Deplacement en haur de Pacman
	_dir = 1;
	if (_map[(((_posp[1] - 1) * _width) + _posp[0])] == '=') {
		return false;
	}
	if (_map[((_posp[1] - 1) * _width) + (_posp[0])] == '.'
		|| _map[((_posp[1] - 1) * _width) + (_posp[0])] == 'o') {
		_food--;
		_score += 100;
	}
	if (_map[((_posp[1] - 1) * _width) + (_posp[0])] == 'o') {
		_timeGod = _time;
		_god = true;
	}
	_map[(((_posp[1] - 1) * _width) + _posp[0])] = 'X';
	_map[((_posp[1]) * _width) + _posp[0]] = ' ';
	_posp[1]--;
	return true;
}

bool Arcade::Pacman::moveDownP() // dir = 2
{
	// Deplacement en bas de Pacman
	_dir = 2;
	if (_map[((_posp[1] + 1) * _width) + _posp[0]] == '='){
		return false;
	}
	if (_map[((_posp[1] + 1) * _width) + (_posp[0])] == '.'
	    || _map[((_posp[1] + 1) * _width) + (_posp[0])] == 'o'){
		_food--;
		_score += 100;
	}
	if (_map[((_posp[1] + 1) * _width) + (_posp[0])] == 'o') {
		_timeGod = _time;
		_god = true;
	}
	_map[((_posp[1] + 1) * _width) + _posp[0]] = 'X';
	_map[((_posp[1]) * _width) + _posp[0]] = ' ';
	_posp[1]++;
	return true;
}

bool Arcade::Pacman::moveLeftP() // dir = 3
{
	// Deplacement à gauche de Pacman
	_dir = 3;
	if (_map[((_posp[1]) * _width) + (_posp[0] - 1)] == '='){
		return false;
	}
	if (_map[((_posp[1]) * _width) + (_posp[0] - 1)] == '.'
		|| _map[((_posp[1]) * _width) + (_posp[0] - 1)] == 'o'){
		_food--;
		_score += 100;
	}
	if (_map[((_posp[1]) * _width) + (_posp[0] - 1)] == 'o') {
		_timeGod = _time;
		_god = true;
	}
	_map[((_posp[1]) * _width) + (_posp[0] - 1)] = 'X';
	_map[((_posp[1]) * _width) + _posp[0]] = ' ';
	_posp[0]--;
	return true;
}

bool Arcade::Pacman::moveRightP() // dir = 4
{
	// Deplacement à droite de Pacman
	_dir = 4;
	if (_map[((_posp[1]) * _width) + (_posp[0] + 1)] == '='){
		return false;
	}
	if (_map[((_posp[1]) * _width) + (_posp[0] + 1)] == '.'
		|| _map[((_posp[1]) * _width) + (_posp[0] + 1)] == 'o') {
		_food--;
		_score += 100;
	}
	if (_map[((_posp[1]) * _width) + (_posp[0] + 1)] == 'o') {
		_timeGod = _time;
		_god = true;
	}
	_map[((_posp[1]) * _width) + (_posp[0] + 1)] = 'X';
	_map[((_posp[1]) * _width) + _posp[0]] = ' ';
	_posp[0]++;
	return true;
}

bool Arcade::Pacman::movePacman()
{
	bool ret; // Valeur de retour

	// Deplacement du Pacman
	switch(_dir){
		case 0:
			return false;
		case 1:
			ret = moveUpP();
			break;
		case 2:
			ret = moveDownP();
			break;
		case 3:
			ret = moveLeftP();
			break;
		case 4:
			ret = moveRightP();
			break;
	}
	return ret;
}

// FANTOM

// _posf[i][2] = dir = 1
bool Arcade::Pacman::moveUpF(std::vector<size_t> &pos, char sym)
{
	// Déplacement en bas d'un fantom
	pos[2] = 1;
	if (_map[(((pos[1] - 1) * _width) + pos[0])] == '='
	    || isNum(_map[(((pos[1] - 1) * _width) + pos[0])])) {
		pos[2] = 0;
		return false;
	}
	_map[((pos[1]) * _width) + pos[0]] = pos[3];
	pos[3] = _map[(((pos[1] - 1) * _width) + pos[0])];
	_map[(((pos[1] - 1) * _width) + pos[0])] = sym;
	pos[1]--;
	return true;

}

// _posf[i][2] = dir = 2
bool Arcade::Pacman::moveDownF(std::vector<size_t> &pos, char sym)
{
	// Déplacement en bas d'un fantom
	pos[2] = 2;
	if (_map[(((pos[1] + 1) * _width) + pos[0])] == '='
		|| isNum(_map[(((pos[1] + 1) * _width) + pos[0])])) {
		pos[2] = 0;
		return false;
	}
	_map[((pos[1] ) * _width) + pos[0]] = pos[3];
	pos[3] = _map[(((pos[1] + 1) * _width) + pos[0])];
	_map[(((pos[1] + 1) * _width) + pos[0])] = sym;
	pos[1]++;
	return true;
}

// _posf[i][2] = dir = 3
bool Arcade::Pacman::moveLeftF(std::vector<size_t> &pos, char sym)
{
	// Déplacement à gauche d'un fantom
	pos[2] = 3;
	if (_map[(((pos[1]) * _width) + pos[0] - 1)] == '='
	    || isNum(_map[(((pos[1]) * _width) + pos[0] - 1)] )) {
		pos[2] = 0;
		return false;
	}
	_map[((pos[1]) * _width) + pos[0]] = pos[3];
	pos[3] = _map[(((pos[1]) * _width) + pos[0] - 1)];
	_map[(((pos[1]) * _width) + pos[0] - 1)] = sym;
	pos[0]--;
	return true;
}

// _posf[i][2] = dir = 4
bool Arcade::Pacman::moveRightF(std::vector<size_t> &pos, char sym)
{
	// Déplacement à droite d'un fantom
	pos[2] = 4;
	if (_map[(((pos[1]) * _width) + pos[0] + 1)] == '='
		|| isNum(_map[(((pos[1]) * _width) + pos[0] + 1)])) {
		pos[2] = 0;
		return false;
	}
	_map[((pos[1]) * _width) + pos[0]] = pos[3];
	pos[3] = _map[(((pos[1]) * _width) + pos[0] + 1)];
	_map[(((pos[1]) * _width) + pos[0] + 1)] = sym;
	pos[0]++;
	return true;
}

bool Arcade::Pacman::moveFantom()
{
	bool ret; // Valeur de retour

	for (int i = 0 ; i != 4 ; i++){
		if (_posf[i][0] >= 12 && _posf[i][0] <= 14
			&& _posf[i][1] >= 12 && _posf[i][1] <= 14
			&& _time >= 10) { // Si les fantomes sont dans la room
			ret = exitRoom(i);
		} else { // Si les fantom ne sont pas dans leur room
			if (_posf[i][2] != 0) { // Si ils n'ont pas de direction
				if (findIntersection(i))
					findDirection(i);
				ret = dirFantom(i);
			} else { // Si ils sont sortis !
				findDirection(i);
				ret = dirFantom(i);
			}
		}
	}
	return ret;
}

// count the number of intersection for the fantom
// if > 3 Fantom choose a new direction
bool Arcade::Pacman::findIntersection(int nb){
	int count = 0;

	if (_map[_posf[nb][0] + ((_posf[nb][1] - 1) * _width)] != '=')
		count++;
	if (_map[_posf[nb][0] + ((_posf[nb][1] + 1) * _width)] != '=')
		count++;
	if (_map[_posf[nb][0] + 1 + ((_posf[nb][1]) * _width)] != '=')
		count++;
	if (_map[_posf[nb][0] - 1 + ((_posf[nb][1]) * _width)] != '=')
		count++;

	if (count >= 3){
		_posf[nb][2] = 0;
		return true;
	}
	return false;
}

void Arcade::Pacman::findDirection(int nb)
{
	int dir; // Direction aléatoire
	int count = 0; // Si trop grand saute le tour du Fantom afin de ne
	// pas bloquer le jeu

	// if : check si la case au dessus est libre ! dir = 1
	// else if : check si la case au dessous est libre ! dir = 2
	// else if : check si la case a gauche est libre ! dir = 3
	// else if : check si la case a droite est libre ! dir = 4
	// else : dir = 0

	while (_posf[nb][2] == 0 && count < 1000) {
		dir = rand() % 5;
		if (dir == 1
			&& (_map[_posf[nb][0] + ((_posf[nb][1] - 1) * _width)] == '.'
		        || _map[_posf[nb][0] + ((_posf[nb][1] - 1) * _width)] == ' '
			|| _map[_posf[nb][0] + ((_posf[nb][1] - 1) * _width)] == 'X'
		        || _map[_posf[nb][0] + ((_posf[nb][1] - 1) * _width)] == 'o'))
			_posf[nb][2] = 1;
		else if (dir == 2
			&& (_map[_posf[nb][0] + ((_posf[nb][1] + 1) * _width)] == '.'
			|| _map[_posf[nb][0] + ((_posf[nb][1] + 1) * _width)] == ' '
		        || _map[_posf[nb][0] + ((_posf[nb][1] + 1) * _width)] == 'X'
		        || _map[_posf[nb][0] + ((_posf[nb][1] + 1) * _width)] == 'o'))
			_posf[nb][2] = 2;
		else if (dir == 3
			&& (_map[_posf[nb][0] - 1 + ((_posf[nb][1]) * _width)] == '.'
		        || _map[_posf[nb][0] - 1 + ((_posf[nb][1]) * _width)] == ' '
			|| _map[_posf[nb][0] - 1 + ((_posf[nb][1]) * _width)] == 'X'
			|| _map[_posf[nb][0] - 1 + ((_posf[nb][1]) * _width)] == 'o'))
			_posf[nb][2] = 3;
		else if ((dir == 4
			&& ((_map[_posf[nb][0] + 1 + ((_posf[nb][1]) * _width)] == '.')
		        || (_map[_posf[nb][0] + 1 + ((_posf[nb][1]) * _width)] == ' ')
			|| (_map[_posf[nb][0] + 1 + ((_posf[nb][1]) * _width)] == 'X')
			|| (_map[_posf[nb][0] + 1 + ((_posf[nb][1]) * _width)] == 'o'))))
			_posf[nb][2] = 4;
		else
			_posf[nb][2] = 0;
		count++;
	}
}

bool Arcade::Pacman::dirFantom(int nb) // deplace le fantom dans sa direction
{
	bool ret; // Valeur de retour

	// Deplacement d'un Fantom
	switch (_posf[nb][2]) {
		case 1:
			ret = moveUpF(_posf[nb], nb + 1 + 48);
			break;
		case 2:
			ret = moveDownF(_posf[nb], nb + 1 + 48);
			break;
		case 3:
			ret = moveLeftF(_posf[nb], nb + 1 + 48);
			break;
		case 4:
			ret = moveRightF(_posf[nb], nb + 1 + 48);
			break;
	}
	return ret;
}

bool Arcade::Pacman::exitRoom(int i)
{
	// Déplace les fantom dans leur room afin qu'il sortent !

	if (_posf[i][0] > 13 && _map[_width * _posf[i][1] + 13] == ' '){
		_map[_width * _posf[i][1] + 14] = _posf[i][3];
		_posf[i][3] = _map[_width * _posf[i][1] + 13];
		_map[_width * _posf[i][1] + 13] = i + 1 + 48;
		_posf[i][0]--;
		_posf[i][2] = 0;
		return true;
	} else if (_posf[i][0] < 13
	           && _map[_width * _posf[i][1] + 13] == ' ') {
		_map[_width * _posf[i][1] + 12] = _posf[i][3];
		_posf[i][3] = _map[_width * _posf[i][1] + 13];
		_map[_width * _posf[i][1] + 13] = i + 1 + 48;
		_posf[i][0]++;
		_posf[i][2] = 0;
		return true;
	}
	if (_posf[i][0] == 13 && _posf[i][1] <= 14 && _posf[i][1] >= 12
		&& (_map[_width * (_posf[i][1] - 1) + _posf[i][0]] == ' '
	        || _map[_width * (_posf[i][1] - 1) + _posf[i][0]] == '.'
	        || _map[_width * (_posf[i][1] - 1) + _posf[i][0]] == '_')) {
		_map[_width * (_posf[i][1]) + _posf[i][0]] = _posf[i][3];
		_posf[i][3] = _map[_width * (_posf[i][1] - 1) + _posf[i][0]];
		_map[_width * (_posf[i][1] - 1) + _posf[i][0]] = i + 1 + 48;
		_posf[i][1]--;
		_posf[i][2] = 0;
		return true;
	}
	return false;
}

/*
** Other
*/

bool Arcade::Pacman::isNum(char num)
{
	return num >= '1' && num <= '9';
}

void Arcade::Pacman::countFood()
{
	// Compte le nombre de "pacgums" sur la map
	for (size_t i = 0 ; i != _map.size() ; i++) {
		if (_map[i] == '.' || _map[i] == 'o')
			_food++;
	}
}

/*
**  Display
*/

void Arcade::Pacman::printMap()
{
	std::cout << "La taille de la map : " << _map.size() << std::endl << std::endl;
	for (size_t i = 0 ; i != _map.size() ; i++) {
		std::cout << _map[i] ;
		if (i % (_width) == 27 && i != 0 ) {
			std::cout << '|' << i << std::endl;
		}
	}
	std::cout << std::endl;
}

void Arcade::Pacman::printLine(int nb)
{
	std::cout << "La ligne n " << nb << " : " << std::endl;
	for (size_t i = 0 ; i != _width ; i++) {
		std::cout << _map[i + (_width * nb)];
	}
	std::cout << std::endl;
}


/*
**  Getter
*/

size_t Arcade::Pacman::getScore()
{
	// Retourne le score du joueur actuel
	return _score;
}

int Arcade::Pacman::getDir()
{
	// Retourne la direction de pacman
	return _dir;
}

std::vector<size_t>& Arcade::Pacman::getPacmanPos()
{
	// Retourne le vecteur de position de pacman
	return _posp;
}

std::vector<std::vector<size_t>> Arcade::Pacman::getFantomPos()
{
	// Retourne le vector contenant les vector des positions des fantomes
	return _posf;
}

const std::string Arcade::Pacman::getName() const
{
	return _name;
}
