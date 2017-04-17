#ifndef _ECE_OTHELLO_PLAYERS_HUMAN_HPP_
	#define _ECE_OTHELLO_PLAYERS_HUMAN_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "uiplayer.hpp"

	namespace Othello {
		namespace Players {
			class Human : public UIPlayer {
				public:
					Human( std::string name, Othello::Board::Pun::Colors color );

					Othello::Board::Move getMove();
			};
		}
	}

#endif
