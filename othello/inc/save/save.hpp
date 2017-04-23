#ifndef _ECE_OTHELLO_SAVE_SAVE_HPP_
	#define _ECE_OTHELLO_SAVE_SAVE_HPP_

	#include <iostream>
	#include <fstream>
	#include <string>
	#include <vector>
	#include "../board/gameboardconstants.hpp"
	#include "../board/pun.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Players
		namespace Players{
			/// \class Player
			/// \brief class représentant un joueur quelconque
			class Player;
		}

		/// \namespace Save
		namespace Save {

		    /// \struct Save
		    /// \brief structure de sauvegarde
			struct Save {
				Othello::Board::Pun::Colors board[ Othello::Board::sizeEdge ][ Othello::Board::sizeEdge ];
				uint64_t emptyNeighbors;
				Othello::Board::PunCount count;
				std::vector<Othello::Players::Player*> players;
				unsigned char currentPlayer;
			};
		}
	}

#endif
