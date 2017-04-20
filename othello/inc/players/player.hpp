#ifndef _ECE_OTHELLO_PLAYERS_PLAYER_HPP_
	#define _ECE_OTHELLO_PLAYERS_PLAYER_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "../board/pun.hpp"
	#include "../board/move.hpp"
	#include "../board/gameboard.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Players
		namespace Players {
		    /// \class Player player.hpp
			class Player {
				protected:
					std::string m_name;
					Othello::Board::Pun::Colors m_color;
					bool m_canPlay = true;
					unsigned char m_punCount = 0;
					Othello::Board::GameBoard* m_board;

				public:
					/// \fn PlayerOverloadConstructor
					Player( std::string name, Othello::Board::Pun::Colors color );

					/// \fn getNameGetter
					const std::string &getName() const;
					/// \fn getColorGetter
					Othello::Board::Pun::Colors getColor() const;
					/// \fn canPlay
					bool canPlay() const;
					/// \fn getPunCountGetter
					unsigned char getPunCount() const;

					/// \fn setCanPlaySetter
					void setCanPlay();
					/// \fn setCannotPlaySetter
					void setCannotPlay();
					/// \fn setPunCountSetter
					void setPunCount( unsigned char punCount );
					/// \fn setBoardSetter
					void setBoard( Othello::Board::GameBoard* board );

					/// \fn getMove
					virtual Othello::Board::Move getMove() = 0;
			};
		}
	}

#endif
