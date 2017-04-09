#ifndef ARTIFICIAL_HPP_INCLUDED
#define ARTIFICIAL_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"

class IA : public Player {
	private:

		//dunno yet

	public:

		std::pair<int, int> ask_for_move();
};


#endif // ARTIFICIAL_HPP_INCLUDED
