cmake_minimum_required(VERSION 3.5)
project(ECE_Othello)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    othello/inc/players/simpleai.hpp
    othello/inc/board/gameboard.hpp
    othello/inc/game.hpp
    othello/inc/players/human.hpp
    othello/inc/board/pun.hpp
    othello/inc/players/player.hpp
    othello/players/simpleai.cpp
        othello/board/gameboard.cpp
        othello/game.cpp
        othello/players/human.cpp
        main.cpp
        othello/players/player.cpp othello/board/move.cpp
    othello/inc/board/move.hpp
        othello/board/valid_move.cpp
    othello/inc/board/valid_move.hpp
        othello/board/direction_vector.cpp
    othello/inc/board/direction_vector.hpp
    othello/inc/ui/games/gameui.hpp
    othello/inc/ui/games/gamecliui.hpp
    othello/ui/games/gamecliui.cpp
        cli/cli.hpp
        cli/cli.cpp
        cli/menu/menu.hpp
        cli/menu/menu.cpp
)

add_executable(ECE_Othello ${SOURCE_FILES})

if(UNIX)
    target_link_libraries(ECE_Othello ncurses)
endif(UNIX)