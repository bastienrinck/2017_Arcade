//
// Created by rectoria on 06/03/18.
//

#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "IGameLib.hpp"

namespace Arcade {
	class Pacman : public IGameLib {
	public:
		Pacman();

		~Pacman() final = default;

		/* Get the name of the game */
		const std::string getName() const final;

		/* Resources handling */
		// Initializes the library
		bool init() final;

		// Unloads the library
		bool stop() final;

		// Processes the key obtained by the IGraphicLib from the user to update the game state
		bool applyEvent(Arcade::Keys) final;

		// Updates the game state. (Move the player forward and/or move the NPCs)
		bool update() final;

		// Renders the game state to the screen. This should call IGraphicLib::refresh() to display content to the user.
		void refresh(IGraphicLib&) final;

		// Open file 'map' and load map
		void loadMap();

		// Movement of Pacman
		bool moveUpP();
		bool moveDownP();
		bool moveLeftP();
		bool moveRightP();

		//Movement of Fantom
		bool moveUpF(std::vector<size_t>&, char sym);
		bool moveDownF(std::vector<size_t>&, char sym);
		bool moveLeftF(std::vector<size_t>&, char sym);
		bool moveRightF(std::vector<size_t>&, char sym);

		// Select new to direction for the Fantom
		void findDirection(int);

		// Find intersection for Fantom
		bool findIntersection(int);

		// Move Fantom to his direction (_posf[i][2])
		bool dirFantom(int i);

		// Choose direction of Pacman
		bool movePacman();

		// Chosse direction of Fantom
		bool moveFantom();

		// Put the Fantom out of the room
		bool exitRoom(int);

		// Get Score of the player
		size_t getScore() final;

		// Get Direction of Pacman
		int getDir();

		// Get Position of Pacman
		std::vector<size_t>& getPacmanPos();

		// Get Position of Fantom
		std::vector<std::vector<size_t>> getFantomPos();

		// Set position of Pacman & Fantom
		void initPosition();

		// Check end condition
		bool end_condition();

		// Check if is a num
		bool isNum(char);

		// Count number of food
		void countFood();

		// Clear the value
		void clearValue();

		// Fantom to House
		void goToHouse();

		// Set value of Fantom
		void setValue(size_t, size_t, size_t, size_t, int);

	private:
		// Name of the game
		std::string _name = "Pacman";

		// Map du jeu
		std::vector<char> _map;

		// Hauteur de la map
		size_t _height = 31;

		// Largeur de la map
		size_t _width = 28;

		// Score actuel du joueur
		size_t _score = 0;

		// Durée de jeu
		size_t _time = 0;

		// Start time
		size_t _startTime;

		// God mod time
		size_t _timeGod = 0;

		// Contient la position du Pacman
		std::vector<size_t> _posp;

		// Contient la position de tous les fantômes !
		std::vector<std::vector<size_t>> _posf;

		// Direction séléctionné pour le Pacman
		int _dir = 0; // x en position 0 | y en position 1

		// Si le GodMod est activé
		bool _god = false;

		// Le nombre de truc a bouffer
		int _food = 0;

		// Map par défault si le fichier 'map.txt' n'est pas trouvé !
		const std::vector<char> _defaultMap = {
			'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=',
			'=','.','.','.','.','.','.','.','.','.','.','.','.','=','=','.','.','.','.','.','.','.','.','.','.','.','.','=',
			'=','.','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','.','=',
			'=','o','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','o','=',
			'=','.','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','.','=',
			'=','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','=',
			'=','.','=','=','=','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','=','=','=','.','=',
			'=','.','=','=','=','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','=','=','=','.','=',
			'=','.','.','.','.','.','.','=','=','.','.','.','.','=','=','.','.','.','.','=','=','.','.','.','.','.','.','=',
			'=','=','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','=','=',
			'|','|','|','|','|','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','|','|','|','|','|',
			'|','|','|','|','|','=','.','=','=','.','.','.','.','.','.','.','.','.','=','=','=','.','=','|','|','|','|','|',
			'|','|','|','|','|','=','.','=','=','.','.','=','=','_','=','=','.','.','=','=','=','.','=','|','|','|','|','|',
			'=','=','=','=','=','=','.','=','=','.','.','=','1',' ','4','=','.','.','=','=','=','.','=','=','=','=','=','=',
			'|','|','|','|','|','=','.','.','.','.','.','=','2',' ','3','=','.','.','.','.','.','.','=','|','|','|','|','|',
			'=','=','=','=','=','=','.','=','=','.','.','=','=','=','=','=','.','.','=','=','=','.','=','=','=','=','=','=',
			'|','|','|','|','|','=','.','=','=','.','.','.','.','.','.','.','.','.','=','=','=','.','=','|','|','|','|','|',
			'|','|','|','|','|','=','.','=','=','.','.','.','.','.','.','.','.','.','.','=','=','.','=','|','|','|','|','|',
			'|','|','|','|','|','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','|','|','|','|','|',
			'=','=','=','=','=','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','=','=','=','=','=',
			'=','.','.','.','.','.','.','.','.','.','.','.','.','=','=','.','.','.','.','.','.','.','.','.','.','.','.','=',
			'=','.','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','.','=',
			'=','.','=','=','=','=','.','=','=','=','=','=','.','=','=','.','=','=','=','=','=','.','=','=','=','=','.','=',
			'=','o','.','.','=','=','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','=','=','.','.','o','=',
			'=','=','=','.','=','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','=','.','=','=','=',
			'=','=','=','.','=','=','.','=','=','.','=','=','=','=','=','=','=','=','.','=','=','.','=','=','.','=','=','=',
			'=','.','.','.','.','.','.','=','=','.','.','.','.','=','=','.','.','.','.','=','=','.','.','.','.','.','.','=',
			'=','.','=','=','=','=','=','=','=','=','=','=','.','=','=','.','=','=','=','=','=','=','=','=','=','=','.','=',
			'=','.','=','=','=','=','=','=','=','=','=','=','.','=','=','.','=','=','=','=','=','=','=','=','=','=','.','=',
			'=','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','X','=',
			'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=',
		};
	};
}
#endif
