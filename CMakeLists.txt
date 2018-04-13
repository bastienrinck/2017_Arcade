cmake_minimum_required(VERSION 3.9)
project(cpp_arcade)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        /interfaces/
        /include/
        /src/menu/
)

add_executable(cpp_arcade
        games/nibbler/Nibbler.cpp
        games/nibbler/Nibbler.hpp
        games/pacman/Pacman.cpp
        games/pacman/Pacman.hpp
        include/Color.cpp
        include/Color.hpp
        include/Keys.hpp
        include/PixelBox.cpp
        include/PixelBox.hpp
        include/TextBox.cpp
        include/TextBox.hpp
        include/Vect.hpp
        interfaces/IGameLib.hpp
        interfaces/IGraphicLib.hpp
        lib/nCurses/NCurses.cpp
        lib/nCurses/NCurses.hpp
        lib/SDL2/Sdl2.cpp
        lib/SDL2/Sdl2.hpp
        lib/SFML/Sfml.cpp
        lib/SFML/Sfml.hpp
        src/core/Core.cpp
        src/core/Core.hpp
        src/menu/Menu.cpp
        src/menu/Menu.hpp
        src/score/Score.cpp
        src/score/Score.hpp
        src/main.cpp
        templates/DLLoader.hpp)
