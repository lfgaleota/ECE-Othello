#ifndef _ECE_OTHELLO_SAVE_SAVEMANAGER_HPP_
	#define _ECE_OTHELLO_SAVE_SAVEMANAGER_HPP_

	#include <fstream>
	#include <sstream>
	#include "save.hpp"
	#include "../players/human.hpp"
	#include "../players/simpleai.hpp"
	#include "../players/enhancedai.hpp"

	namespace Othello {
		namespace Save {
			class SaveManager {
				private:
					static const std::string savePath;

					static bool dumpBoard( Othello::Board::GameBoard* ref, std::ostream& saveFile );
					static bool dumpEmptyNeighbors( Othello::Board::GameBoard* ref, std::ostream& saveFile );
					static bool dumpPunCounts( Othello::Board::GameBoard* ref, std::ostream& saveFile );
					static bool dumpPlayers( std::vector<Othello::Players::Player*>& ref, std::vector<Othello::Players::Player*>::iterator& current, std::ostream& saveFile );

					static Othello::Players::Player* init( Othello::Players::Player::Type type, std::string name, Othello::Board::Pun::Colors color );

					static bool loadBoard( Save& save, std::string value );
					static bool loadEmptyNeighbors( Save& save, std::string value );
					static bool loadPunCounts( Save& save, std::string value );
					static bool loadPlayers( Save& save, std::string value );

				public:
					static Save load();
					static void save( Othello::Board::GameBoard* board, std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& current );
					static bool check();
			};
		}
	}

#endif
