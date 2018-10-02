# 2017_Arcade
Game terminal with loading of graphic library and game during runtime.

## Stock Libraries
**Graphical**

SFML - [wikipedia](https://en.wikipedia.org/wiki/Simple_and_Fast_Multimedia_Library)

SDL2 - [wikipedia](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer)

nCurses - [wikipedia](https://en.wikipedia.org/wiki/Ncurses)

**Game**

Pacman - [wikipedia](https://en.wikipedia.org/wiki/Pac-Man)

Nibbler - [wikipedia](https://en.wikipedia.org/wiki/Nibbler_(video_game))

## Adding libraries
```
In order for the program to load your library, you must ensure that it meets the specifications listed in /2017_Arcade-Spec
```

![Menu](https://imgur.com/5dMRhxi.png)
Main menu

![Scores](https://imgur.com/2s1zDXj.png)
Highscores

![Pacman SFML](https://imgur.com/IfgGPTY.png)
Pacman - SFML


![Nibbler ncruses](https://imgur.com/ockZqL5.png)
Nibbler - nCurses

## Usage
```
./arcade [library name]
#ex: lib_arcade_sfml.so
#Libraries are available in ./lib directory
```
## Commands

```
Left/Right arrow keys: Graphical library hot swap
Up/Down arrow keys: Game hot swap (pausing the previous one)
TAB (menu): Show highscores
ESC: Exit game/Exit program
```
## Ingame commands
```
Each game controls its inputs, except for the keys listed below.
ex: Spacebar -> Reset on stock games.
```

## Authors
* Bastien Rinck
* Nicolas Schmitt
* Victor Weber
