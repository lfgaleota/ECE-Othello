#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "board.hpp"

class Game {
	private :

		bool m_turn; //player turn ?
		Board m_board; //game board

	public :

		Game();

		~Game();

		void display();


};


#endif // GAME_HPP_INCLUDED
