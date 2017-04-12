cmake_minimum_required(VERSION 3.5)
project(ECE_Othello)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        inc/players/simpleia.hpp
        inc/board/gameboard.hpp
        inc/game.hpp
        inc/players/human.hpp
        inc/board/pun.hpp
        inc/players/player.hpp
        othello/players/simpleia.cpp
        othello/board/gameboard.cpp
        othello/game.cpp
        othello/players/human.cpp
        main.cpp
        othello/players/player.cpp othello/board/move.cpp
        inc/board/move.hpp
        othello/board/valid_move.cpp
        inc/board/valid_move.hpp
        othello/board/direction_vector.cpp
        inc/board/direction_vector.hpp
        inc/ui/games/gameui.hpp
        inc/ui/games/gamecliui.hpp
        ui/games/gamecliui.cpp
        cli/cli.hpp
        cli/cli.cpp
)

add_executable(ECE_Othello ${SOURCE_FILES})

if(UNIX)
    target_link_libraries(ECE_Othello ncurses)
endif(UNIX)