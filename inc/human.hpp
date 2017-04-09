#ifndef HUMAN_H_INCLUDED
#define HUMAN_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"

class Human : public Player {
	private :

		//dunno yet

	public :

		std::pair<int, int> ask_for_move();
};


#endif // HUMAN_H_INCLUDED
