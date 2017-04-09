#ifndef HUMAN_HPP_INCLUDED
#define HUMAN_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"

class Human : public Player {
	private:

		//dunno yet

	public:

		std::pair<int, int> ask_for_move();
};


#endif // HUMAN_HPP_INCLUDED
