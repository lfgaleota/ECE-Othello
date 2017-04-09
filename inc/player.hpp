#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>


class Player {
	protected:
		std::string name;

	public:
		Player( std::string name );

		virtual std::pair<int, int> ask_for_move();
};


#endif // PLAYER_H_INCLUDED
