#ifndef _ECE_OTHELLO_PLAYERS_SIMPLEIA_HPP_
	#define _ECE_OTHELLO_PLAYERS_SIMPLEIA_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "player.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Players
		namespace Players {
		    /// \class SimpleAI simpleai.hpp
			class SimpleAI : public Player {
				public:
					/// \fn SimpleAIOverloadConstructor
					SimpleAI( std::string name, Othello::Board::Pun::Colors color );

					/// \fn getMove
					Othello::Board::Move getMove();
			};
		}
	}

#endif
