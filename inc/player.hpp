#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "pun.hpp"
#include "move.hpp"


class Player {
	protected:
		std::string m_name;
		Pun::Colors m_color;

	public:
		Player( std::string name, Pun::Colors color );

		const std::string &getName() const;
		Pun::Colors getColor() const;

		virtual Move getMove() = 0;
};


#endif // PLAYER_H_INCLUDED
