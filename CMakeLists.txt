cmake_minimum_required(VERSION 3.5)
project(ECE_Othello)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        inc/artificial.hpp
        inc/board.hpp
        inc/game.hpp
        inc/human.hpp
        inc/othello.hpp
        inc/player.hpp
        artificial.cpp
        board.cpp
        game.cpp
        human.cpp
        main.cpp
        player.cpp)

add_executable(ECE_Othello ${SOURCE_FILES})