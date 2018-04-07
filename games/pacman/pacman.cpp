/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "pacman.hpp"

// Map par défault si le fichier 'map.txt' n'est pas trouvé !
static const std::vector<char> default_map = {
'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','\n',
'=','.','.','.','.','.','.','.','.','.','.','.','.','=','=','.','.','.','.','.','.','.','.','.','.','.','.','=','\n',
'=','.','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','.','=','\n',
'=','o','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','o','=','\n',
'=','.','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','.','=','\n',
'=','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','=','\n',
'=','.','=','=','=','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','=','=','=','.','=','\n',
'=','.','=','=','=','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','=','=','=','.','=','\n',
'=','.','.','.','.','.','.','=','=','.','.','.','.','=','=','.','.','.','.','=','=','.','.','.','.','.','.','=','\n',
'=','=','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','=','=','\n',
'|','|','|','|','|','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','|','|','|','|','|','\n',
'|','|','|','|','|','=','.','=','=','.','.','.','.','.','.','.','.','.','=','=','=','.','=','|','|','|','|','|','\n',
'|','|','|','|','|','=','.','=','=','.','.','=','=','_','=','=','.','.','=','=','=','.','=','|','|','|','|','|','\n',
'=','=','=','=','=','=','.','=','=','.','.','=','1',' ','4','=','.','.','=','=','=','.','=','=','=','=','=','=','\n',
'|','|','|','|','|','=','.','.','.','.','.','=','2',' ','3','=','.','.','.','.','.','.','=','|','|','|','|','|','\n','=','=','=','=','=','=','.','=','=','.','.','=','=','=','=','=','.','.','=','=','=','.','=','=','=','=','=','=','\n',
'|','|','|','|','|','=','.','=','=','.','.','.','.','.','.','.','.','.','=','=','=','.','=','|','|','|','|','|','\n',
'|','|','|','|','|','=','.','=','=','.','.','.','.','.','.','.','.','.','.','=','=','.','=','|','|','|','|','|','\n',
'|','|','|','|','|','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','|','|','|','|','|','\n',
'=','=','=','=','=','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','=','=','=','=','=','\n',
'=','.','.','.','.','.','.','.','.','.','.','.','.','=','=','.','.','.','.','.','.','.','.','.','.','.','.','=','\n',
'=','.','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','.','=','\n',
'=','.','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','.','=','\n',
'=','o','.','.','=','=','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','=','=','.','.','o','=','\n',
'=','=','=','.','=','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','=','.','=','=','=','\n',
'=','=','=','.','=','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','=','.','=','=','=','\n',
'=','.','.','.','.','.','.','=','=','.','.','.','.','=','=','.','.','.','.','=','=','.','.','.','.','.','.','=','\n',
'=','.','=','=','=','=','=','=','=','=','=','=','.','=','=','.','=','=','=','=','=','=','=','=','=','=','.','=','\n',
'=','.','=','=','=','=','=','=','=','=','=','=','.','=','=','.','=','=','=','=','=','=','=','=','=','=','.','=','\n',
'=','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','X','=','\n',
'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','\n',
};

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

const std::string Arcade::Pacman::getName() const
{
	return _name;
}

bool Arcade::Pacman::init()
{

	loadMap();
	initPosition();
	std::cout << _map[(14 - 1) * 28 + (13 - 1)] << std::endl;
	return true;
}

void Arcade::Pacman::initPosition()
{
	_pos_p.push_back(27 - 1); // x
	_pos_p.push_back(30 - 1); // y

	std::vector<size_t> one = {13 - 1 , 14 - 1, 0, 32};
	_pos_f.push_back(one);

	std::vector<size_t> two =  {13 - 1 , 15 - 1, 0, 32};
	_pos_f.push_back(two);

	std::vector<size_t> three = {15 - 1 , 15 - 1, 0, 32};
	_pos_f.push_back(three);

	std::vector<size_t> four = {15 - 1 , 14 - 1, 0, 32};
	_pos_f.push_back(four);

	for (int i = 0 ; i != 4; i++){
		std::cout << "nb : " << i << std::endl;
		std::cout << "size : " << _pos_f[i].size() << std::endl;
		std::cout << "x : " << _pos_f[i][0] << std::endl;
		std::cout << "y : " << _pos_f[i][1] << std::endl;
		std::cout << _map[_width * _pos_f[i][1] + _pos_f[i][0]] << std::endl;
	}
}

bool Arcade::Pacman::stop()
{
	return true;
}

//bool Arcade::Pacman::close()
//{
//	return true;
//}
//
//bool Arcade::Pacman::open()
//{
//	return true;
//}

bool Arcade::Pacman::applyEvent(Arcade::Keys keys)
{
	keys = keys;
	return true;
}

bool Arcade::Pacman::update()
{
	return true;
}

void Arcade::Pacman::refresh(IGraphicLib& gl)
{
//	static int idx = 0;
//	auto r = Arcade::PixelBox(Arcade::Vect<size_t>(gl.getMaxX(), gl.getMaxY()), Vect<size_t>(), Arcade::Color(255, 0, 0, 255));
//	auto g = Arcade::PixelBox(Arcade::Vect<size_t>(gl.getMaxX(), gl.getMaxY()), Vect<size_t>(), Arcade::Color(0, 255, 0, 255));
//	auto b = Arcade::PixelBox(Arcade::Vect<size_t>(gl.getMaxX(), gl.getMaxY()), Vect<size_t>(), Arcade::Color(0, 0, 255, 255));
//
//	gl.clearWindow();
//	if (idx == 0)
//		gl.drawText(_tB);
//		std::cout << "Le tB mysterieux" << std::endl;
//	else if (idx == 1)
//		gl.drawPixelBox(r);
//	else if (idx == 2)
//		gl.drawPixelBox(g);
//	else if (idx == 3)
//		gl.drawPixelBox(b);
//	gl.refreshWindow();
//	idx = idx == 3 ? 0 : idx + 1;

	size_t pWidth = _width * CELL_WIDTH;
	size_t pHeight = _height * CELL_HEIGHT;

	graphicsLib.clearWindow();
	print_background(graphicsLib);
	_pB = Arcade::PixelBox(Arcade::Vect<size_t>(CELL_WIDTH, CELL_HEIGHT),
	                       Arcade::Vect<size_t>(), Arcade::Color(255, 0, 0, 255));
	for (auto cell : _snake) {
		_pB.setX((graphicsLib.getMaxX() / 2) - (pWidth / 2) +
		         (cell.getX() * CELL_WIDTH));
		_pB.setY((graphicsLib.getMaxY() / 2) - (pHeight / 2) +
		         (cell.getY() * CELL_HEIGHT));
		graphicsLib.drawPixelBox(_pB);
	}
	graphicsLib.refreshWindow();

}

void Arcade::Pacman::loadMap()
{
	std::ifstream input("map.txt");
	char tmp;

	if (!input) {
		std::cout << "Error : file 'map.txt' not found. The default "
	       "map is loaded" << std::endl;
		_map = default_map;
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

//PACMAN

bool Arcade::Pacman::moveUpP() // dir = 1
{
	std::cout << "moveUpP() " << std::endl;
	_dir = 1;
	if (_map[(((_pos_p[1] - 1) * _width) + _pos_p[0])] == '=') {
		std::cout << "Impossible to moveUp" << std::endl;
		return false;
	}
	if (_map[((_pos_p[1] - 1) * _width) + (_pos_p[0])] == '.')
		_score += 100;
	_map[(((_pos_p[1] - 1) * _width) + _pos_p[0])] = 'X';
	_map[((_pos_p[1]) * _width) + _pos_p[0]] = ' ';
	_pos_p[1]--;
	return true;
}

bool Arcade::Pacman::moveDownP() // dir = 2
{
	std::cout << "moveDownP() " << std::endl;
	_dir = 2;
	if (_map[((_pos_p[1] + 1) * _width) + _pos_p[0]] == '='){
		std::cout << "Impossible to moveDown" << std::endl;
		return false;
	}
	if (_map[((_pos_p[1] + 1) * _width) + (_pos_p[0])] == '.')
		_score += 100;
	_map[((_pos_p[1] + 1) * _width) + _pos_p[0]] = 'X';
	_map[((_pos_p[1]) * _width) + _pos_p[0]] = ' ';
	_pos_p[1]++;
	return true;
}

bool Arcade::Pacman::moveLeftP() // dir = 3
{
	std::cout << "moveLeftP() " << std::endl;
	_dir = 3;
	if (_map[((_pos_p[1]) * _width) + (_pos_p[0] - 1)] == '='){
		std::cout << "Impossible to moveLeft" << std::endl;
		return false;
	}
	if (_map[((_pos_p[1]) * _width) + (_pos_p[0] - 1)] == '.')
		_score += 100;
	_map[((_pos_p[1]) * _width) + (_pos_p[0] - 1)] = 'X';
	_map[((_pos_p[1]) * _width) + _pos_p[0]] = ' ';
	_pos_p[0]--;
	return true;
}

bool Arcade::Pacman::moveRightP() // dir = 4
{
	std::cout << "moveRightP() " << std::endl;
	_dir = 4;
	if (_map[((_pos_p[1]) * _width) + (_pos_p[0] + 1)] == '='){
		std::cout << "Impossible to moveRight" << std::endl;
		return false;
	}
	if (_map[((_pos_p[1]) * _width) + (_pos_p[0] + 1)] == '.')
		_score += 100;
	_map[((_pos_p[1]) * _width) + (_pos_p[0] + 1)] = 'X';
	_map[((_pos_p[1]) * _width) + _pos_p[0]] = ' ';
	_pos_p[0]++;
	return true;
}

bool Arcade::Pacman::movePacman()
{
	bool ret;

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
	if (ret) {
		printMap();
		std::cout << std::endl << std::endl;
	}
	return ret;
}

//FANTOM

// _pos_f[i][2] = dir = 1
bool Arcade::Pacman::moveUpF(std::vector<size_t> &pos, char sym)
{
	std::cout << "moveUpF() " << std::endl;
	pos[2] = 1;
	if (_map[(((pos[1] - 1) * _width) + pos[0])] == '=') {
		std::cout << "Impossible to moveUp" << std::endl;
		pos[2] = 0;
		return false;
	}
	_map[((pos[1]) * _width) + pos[0]] = pos[3];
	pos[3] = _map[(((pos[1] - 1) * _width) + pos[0])];
	_map[(((pos[1] - 1) * _width) + pos[0])] = sym;
	pos[1]--;
	return true;

}

// _pos_f[i][2] = dir = 2
bool Arcade::Pacman::moveDownF(std::vector<size_t> &pos, char sym)
{
	std::cout << "moveDownF() " << std::endl;
	pos[2] = 2;
	if (_map[(((pos[1] + 1) * _width) + pos[0])] == '=') {
		std::cout << "Impossible to moveDown" << std::endl;
		pos[2] = 0;
		return false;
	}
	_map[((pos[1]) * _width) + pos[0]] = pos[3];
	pos[3] = _map[(((pos[1] + 1) * _width) + pos[0])];
	_map[(((pos[1] + 1) * _width) + pos[0])] = sym;
	pos[1]++;
	return true;
}

// _pos_f[i][2] = dir = 3
bool Arcade::Pacman::moveLeftF(std::vector<size_t> &pos, char sym)
{
	std::cout << "moveLeftF() " << std::endl;
	pos[2] = 3;
	if (_map[(((pos[1]) * _width) + pos[0] - 1)] == '=') {
		std::cout << "Impossible to moveDown" << std::endl;
		pos[2] = 0;
		return false;
	}
	_map[((pos[1]) * _width) + pos[0]] = pos[3];
	pos[3] = _map[(((pos[1]) * _width) + pos[0] - 1)];
	_map[(((pos[1]) * _width) + pos[0] - 1)] = sym;
	pos[0]--;
	return true;
}

// _pos_f[i][2] = dir = 4
bool Arcade::Pacman::moveRightF(std::vector<size_t> &pos, char sym)
{
	std::cout << "moveRightF() " << std::endl;
	pos[2] = 4;
	if (_map[(((pos[1]) * _width) + pos[0] + 1)] == '=') {
		std::cout << "Impossible to moveDown" << std::endl;
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
	bool ret;

	for (int i = 0 ; i != 4 ; i++){
		if (_pos_f[i][0] >= 12 && _pos_f[i][0] <= 14
			&& _pos_f[i][1] >= 12 && _pos_f[i][1] <= 14){
			ret = exitRoom(i);
			printMap();
		} else {
			if (_pos_f[i][2] != 0) {
				if (findIntersection(i))
					findDirection(i);
				ret = dirFantom(i);
				printMap();
			} else {
				findDirection(i);
				ret = dirFantom(i);
				printMap();
			}
		}
	}
	return ret;
}

// count the number of intersection for the fantom
// if > 3 Fantom choose a new direction
bool Arcade::Pacman::findIntersection(int nb){
	int count = 0;

	if (_map[_pos_f[nb][0] + ((_pos_f[nb][1] - 1) * _width)] != '=')
		count++;
	if (_map[_pos_f[nb][0] + ((_pos_f[nb][1] + 1) * _width)] != '=')
		count++;
	if (_map[_pos_f[nb][0] + 1 + ((_pos_f[nb][1]) * _width)] != '=')
		count++;
	if (_map[_pos_f[nb][0] - 1 + ((_pos_f[nb][1] - 1) * _width)] != '=')
		count++;

	if (count >= 3)
		return true;
	return false;
}

void Arcade::Pacman::findDirection(int nb)
{
	srand(time(NULL) * getpid());
	int dir;

	// if : check si la case au dessus est libre ! dir = 1
	// else if : check si la case au dessous est libre ! dir = 2
	// else if : check si la case a gauche est libre ! dir = 3
	// else if : check si la case a droite est libre ! dir = 4
	// else : dir = 0

	while (_pos_f[nb][2] == 0){
		dir = rand() % 5;
		std::cout << "Dir " << dir << std::endl;
//		sleep(2);
//		continue;
		if (dir == 1
			&& (_map[_pos_f[nb][0] + ((_pos_f[nb][1] - 1) * _width)] == '.'
		        || _map[_pos_f[nb][0] + ((_pos_f[nb][1] - 1) * _width)] == ' '
			|| _map[_pos_f[nb][0] + ((_pos_f[nb][1] - 1) * _width)] == 'X'))
			_pos_f[nb][2] = 1;
		else if (dir == 2
			&& (_map[_pos_f[nb][0] + ((_pos_f[nb][1] + 1) * _width)] == '.'
			|| _map[_pos_f[nb][0] + ((_pos_f[nb][1] + 1) * _width)] == ' '
		        || _map[_pos_f[nb][0] + ((_pos_f[nb][1] + 1) * _width)] == 'X'))
			_pos_f[nb][2] = 2;
		else if (dir == 3
			&& (_map[_pos_f[nb][0] - 1 + ((_pos_f[nb][1]) * _width)] == '.'
		        || _map[_pos_f[nb][0] - 1 + ((_pos_f[nb][1]) * _width)] == ' '
		        || _map[_pos_f[nb][0] - 1 + ((_pos_f[nb][1]) * _width)] == 'X'))
			_pos_f[nb][2] = 3;
		else if ((dir == 4
			&& ((_map[_pos_f[nb][0] + 1 + ((_pos_f[nb][1]) * _width)] == '.')
		        || (_map[_pos_f[nb][0] + 1 + ((_pos_f[nb][1]) * _width)] == ' ')
		        || (_map[_pos_f[nb][0] + 1 + ((_pos_f[nb][1]) * _width)] == 'X'))))
			_pos_f[nb][2] = 4;
		else
			_pos_f[nb][2] = 0;
	}
	std::cout << "La direction du Fantom nb " << nb + 1 << " : " <<
	          _pos_f[nb][2] << std::endl;
}

bool Arcade::Pacman::dirFantom(int nb) // deplace le fantom dans sa direction
{
	bool ret;

	switch (_pos_f[nb][2]) {
		case 1:
			ret = moveUpF(_pos_f[nb], nb + 1 + 48);
			break;
		case 2:
			ret = moveDownF(_pos_f[nb], nb + 1 + 48);
			break;
		case 3:
			ret = moveLeftF(_pos_f[nb], nb + 1 + 48);
			break;
		case 4:
			ret = moveRightF(_pos_f[nb], nb + 1 + 48);
			break;
	}
	if (ret){
		printMap();
		std::cout << std::endl << std::endl;
	}
	return ret;
}

bool Arcade::Pacman::exitRoom(int i)
{
	if (_pos_f[i][0] > 13 && _map[_width * _pos_f[i][1] + 13] == ' '){
		_map[_width * _pos_f[i][1] + 14] = _pos_f[i][3];
		_pos_f[i][3] = _map[_width * _pos_f[i][1] + 13];
		_map[_width * _pos_f[i][1] + 13] = i + 1 + 48;
		_pos_f[i][0]--;
		_pos_f[i][2] = 0;
		return true;
	} else if (_pos_f[i][0] < 13
	           && _map[_width * _pos_f[i][1] + 13] == ' ') {
		_map[_width * _pos_f[i][1] + 12] = _pos_f[i][3];
		_pos_f[i][3] = _map[_width * _pos_f[i][1] + 13];
		_map[_width * _pos_f[i][1] + 13] = i + 1 + 48;
		_pos_f[i][0]++;
		_pos_f[i][2] = 0;
		return true;
	}
	if (_pos_f[i][0] == 13 && _pos_f[i][1] <= 14 && _pos_f[i][1] >= 12
		&& (_map[_width * (_pos_f[i][1] - 1) + _pos_f[i][0]] == ' '
	        || _map[_width * (_pos_f[i][1] - 1) + _pos_f[i][0]] == '.'
	        || _map[_width * (_pos_f[i][1] - 1) + _pos_f[i][0]] == '_')) {
		_map[_width * (_pos_f[i][1]) + _pos_f[i][0]] = _pos_f[i][3];
		_pos_f[i][3] = _map[_width * (_pos_f[i][1] - 1) + _pos_f[i][0]];
		_map[_width * (_pos_f[i][1] - 1) + _pos_f[i][0]] = i + 1 + 48;
		_pos_f[i][1]--;
		_pos_f[i][2] = 0;
		return true;
	}
	return false;
}

/*
**  Display
*/

void Arcade::Pacman::printMap()
{
	std::cout << "La taille de la map : " << _map.size() << std::endl << std::endl;
	for (size_t i = 0 ; i != _map.size() ; i++) {
		std::cout << _map[i] ;
		if (i % (_width ) == 27 && i != 0 ) {
			std::cout << '|' << i << std::endl;
		}
	}
	std::cout << std::endl;
//	printLine(0);	printLine(1);	printLine(2);	printLine(3);	printLine(4);	printLine(5);	printLine(6);	printLine(7);	printLine(8);	printLine(9);	printLine(10);
//	printLine(11);	printLine(12);	printLine(13);	printLine(14);	printLine(15);	printLine(16);	printLine(17);	printLine(18);	printLine(19);	printLine(20);
//	printLine(21);	printLine(22);	printLine(23);	printLine(24);	printLine(25);	printLine(26);	printLine(27);	printLine(28);	printLine(29);	printLine(30);
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
	return _score;
}

int Arcade::Pacman::getDir()
{
	return _dir;
}

std::vector<size_t>& Arcade::Pacman::getPacmanPos()
{
	return _pos_p;
}

std::vector<std::vector<size_t>> Arcade::Pacman::getFantomPos()
{
	return _pos_f;
}

/*
int main()
{
	bool test;
	Arcade::Pacman pac;


	pac.init();

	pac.printMap();

//	test = pac.moveDown();
//	if (test){
//		pac.printMap();
//		std::cout << "===========================" << std::endl;
//	}

	test = pac.moveLeftP();
	if (test){
		pac.printMap();
		std::cout << "===========================" << std::endl;
	}

	sleep(2);
	while (1){
		std::cout << "La valeur de dir : " << pac.getDir() << std::endl;
		test = pac.movePacman();
		pac.moveFantom();
		sleep(1);
		if (!test){
			std::cout << "Votre score est de : " << pac.getScore() << std::endl;
			exit(0);
		}
	}

//	test = pac.moveUp();
//	if (test){
//		pac.printMap();
//		std::cout << "===========================" << std::endl;
//	}
//
//	test = pac.moveUp();
//	if (test){
//		pac.printMap();
//		std::cout << "===========================" << std::endl;
//	}
//
//	test = pac.moveUp();
//	if (test){
//		pac.printMap();
//		std::cout << "===========================" << std::endl;
//	}
//
//	test = pac.moveLeft();
//	if (test){
//		pac.printMap();
//		std::cout << "===========================" << std::endl;
//	}
//	test = pac.moveLeft();
//	if (test){
//		pac.printMap();
//		std::cout << "===========================" << std::endl;
//	}
//	test = pac.moveRight();
//	if (test){
//		pac.printMap();
//		std::cout << "===========================" << std::endl;
//	}

	std::cout << "Votre score est de : " << pac.getScore() << std::endl;
}
*/