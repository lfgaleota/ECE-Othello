#ifndef _ECE_OTHELLO_PLAYERS_ENHANCEDAI_HPP_
	#define _ECE_OTHELLO_PLAYERS_ENHANCEDAI_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include <exception>
	#include "uiplayer.hpp"
	#include "../algorithms/minimax.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Players
		namespace Players {
		    /// \class EnhancedAI enhancedai.hpp
			class EnhancedAI : public UIPlayer {
				public:
					/// \fn EnhancedAI
					EnhancedAI( std::string name, Othello::Board::Pun::Colors color );

					/// \fn getMove
					Othello::Board::Move getMove();
			};
		}
	}

#endif
