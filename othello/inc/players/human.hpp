#ifndef _ECE_OTHELLO_PLAYERS_HUMAN_HPP_
	#define _ECE_OTHELLO_PLAYERS_HUMAN_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "uiplayer.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Players
		namespace Players {
		    /// \class Human human.hpp
			class Human : public UIPlayer {
				public:
					/// \fn HumanOverloadConstructor
					/// \param {name, color}
					Human( std::string name, Othello::Board::Pun::Colors color );

					/// \fn getMove
					/// \param {no parameters}
					Othello::Board::Move getMove();
			};
		}
	}

#endif
