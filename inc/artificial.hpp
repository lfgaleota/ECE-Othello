#ifndef ARTIFICIAL_H_INCLUDED
#define ARTIFICIAL_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"

class IA : public Player {
	private :

		//dunno yet

	public :

		std::pair<int, int> ask_for_move();
};


#endif // ARTIFICIAL_H_INCLUDED
