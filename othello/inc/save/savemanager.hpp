#ifndef _ECE_OTHELLO_SAVE_SAVEMANAGER_HPP_
	#define _ECE_OTHELLO_SAVE_SAVEMANAGER_HPP_

	#include <fstream>
	#include <sstream>
	#include "save.hpp"
	#include "../players/human.hpp"
	#include "../players/randomai.hpp"
	#include "../players/simpleai.hpp"
	#include "../players/enhancedai.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Save
		namespace Save {
		    /// \class SaveManager
			class SaveManager {
				private:
					static const std::string savePath;

					/// \fn dumpBoard
					/// \param {gameboard ref, saveFile}
					static bool dumpBoard( Othello::Board::GameBoard* ref, std::ostream& saveFile );
					/// \fn dumbEmptyNeighbors
					/// \param {gameboard ref, saveFile}
					static bool dumpEmptyNeighbors( Othello::Board::GameBoard* ref, std::ostream& saveFile );
					/// \fn dumpPunCounts
					/// \param {gameboard ref, saveFile}
					static bool dumpPunCounts( Othello::Board::GameBoard* ref, std::ostream& saveFile );
					/// \fn dumpPlayers
					/// \param {players ref, current, saveFile}
					static bool dumpPlayers( std::vector<Othello::Players::Player*>& ref, std::vector<Othello::Players::Player*>::iterator& current, std::ostream& saveFile );

					/// \fn init
					/// \param {name, color}
					static Othello::Players::Player* init( Othello::Players::Player::Type type, std::string name, Othello::Board::Pun::Colors color );

					/// \fn loadBoard
					/// \param {value}
					static bool loadBoard( Save& save, std::string value );
					/// \fn loadEmptyNeighbors
					/// \param {value}
					static bool loadEmptyNeighbors( Save& save, std::string value );
					/// \fn loadPunCounts
					/// \param {value}
					static bool loadPunCounts( Save& save, std::string value );
					/// \fn loadPlayers
					/// \param {value}
					static bool loadPlayers( Save& save, std::string value );

				public:
					/// \fn load
					/// \param {}
					static Save load();
					/// \fn save
					/// \param {}
					static void save( Othello::Board::GameBoard* board, std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& current );
					/// \fn check
					/// \param {}
					static bool check();
			};
		}
	}

#endif
