#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "board.hpp"

class Game {
	private:
		Board board; //game board

	public:

		Game();

		~Game();

		void display();


};


#endif // GAME_HPP_INCLUDED
