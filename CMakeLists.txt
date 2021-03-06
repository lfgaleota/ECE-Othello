cmake_minimum_required(VERSION 3.5)
project(ECE_Othello)

option(GPERFTOOL_PROFILER "Activate gperftool CPU Profiler")

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(SOURCE_FILES
    othello/inc/players/randomai.hpp
    othello/inc/board/gameboard.hpp
    othello/inc/game.hpp
    othello/inc/players/human.hpp
    othello/inc/board/pun.hpp
    othello/inc/players/player.hpp
    othello/players/randomai.cpp
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
    othello/board/tree/validmovenode.cpp
    othello/inc/board/tree/validmovenode.hpp
    othello/algorithms/minimax.cpp
    othello/inc/algorithms/minimax.hpp
    othello/inc/board/gameissue.hpp
    othello/players/enhancedai.cpp
    othello/inc/players/enhancedai.hpp
    othello/players/simpleai.cpp
    othello/inc/players/simpleai.hpp
    othello/players/uiplayer.cpp
    othello/inc/players/uiplayer.hpp
    othello/algorithms/heuristics.cpp
    othello/inc/algorithms/heuristics.hpp
    othello/ui/games/clivalidmovetreeviewer.cpp
    othello/inc/ui/games/clivalidmovetreeviewer.hpp
    othello/ui/games/gameallegroui.cpp
    othello/inc/ui/games/gameallegroui.hpp
    othello/ui/games/allegrovalidmovetreeviewer.cpp
    othello/inc/ui/games/allegrovalidmovetreeviewer.hpp
    othello/algorithms/alphabeta.cpp
    othello/inc/algorithms/alphabeta.hpp
    othello/inc/save/save.hpp
    othello/inc/save/savemanager.hpp
    othello/save/savemanager.cpp
    othello/inc/save/savemanager.hpp
    othello/board/pun.cpp
    othello/inc/board/gameboardconstants.hpp
    othello/ui/main/maincliui.cpp
    othello/inc/ui/main/maincliui.hpp
    othello/ui/main/mainallegroui.cpp
    othello/inc/ui/main/mainallegroui.hpp
    othello/ui/audio/FMOD.cpp
    othello/inc/ui/audio/FMOD.hpp
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_impl_agl.cpp
)

if(WIN32)
    set(SOURCE_FILES
        ${SOURCE_FILES}
        othello/inc/winres.h
        othello/winres.o
        win32_SetProcessDpiAware/win32_SetProcessDpiAware.c
        win32_SetProcessDpiAware/win32_SetProcessDpiAware.h
    )
endif(WIN32)

add_executable(ECE_Othello ${SOURCE_FILES})

if(UNIX)
    target_link_libraries(ECE_Othello ncurses pthread)
endif(UNIX)

if(GPERFTOOL_PROFILER)
	target_link_libraries(ECE_Othello profiler)
endif(GPERFTOOL_PROFILER)

if(CMAKE_BUILD_TYPE MATCHES "Release")
	if(CMAKE_COMPILER_IS_GNUCXX)
		set(CMAKE_CXX_FLAGS "-O3")
		set(CMAKE_EXE_LINKER_FLAGS "-s")
	endif(CMAKE_COMPILER_IS_GNUCXX)
endif(CMAKE_BUILD_TYPE MATCHES "Release")

#target_link_libraries(ECE_Othello m z loadpng png jpgalleg alleggl alleg)

target_link_libraries(ECE_Othello m z)

find_package(FMOD REQUIRED)
include_directories(${FMOD_INCLUDE_DIRS})
target_link_libraries(ECE_Othello ${FMOD_LIBRARIES})

find_package(ALLEGRO4 REQUIRED)
include_directories(${ALLEGRO4_INCLUDE_DIRS})
target_link_libraries(ECE_Othello ${ALLEGRO4_LIBRARIES})

if(WIN32)
	target_link_libraries(ECE_Othello opengl32 glu32 winmm gdi32)
else(WIN32)
	target_link_libraries(ECE_Othello GL GLU)
endif(WIN32)
