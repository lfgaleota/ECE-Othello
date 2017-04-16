#ifndef _ECE_OTHELLO_PLAYERS_SIMPLEIA_HPP_
	#define _ECE_OTHELLO_PLAYERS_SIMPLEIA_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "player.hpp"

	namespace Othello {
		namespace Players {
			class SimpleAI : public Player {
				public:
					SimpleAI( std::string name, Othello::Board::Pun::Colors color );

					Othello::Board::Move getMove();
			};
		}
	}

#endif
