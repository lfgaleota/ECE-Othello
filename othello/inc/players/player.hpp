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
					/// \param {color}
					Player( std::string name, Othello::Board::Pun::Colors color );

					/// \fn getNameGetter
					/// \param {no parameters}
					const std::string &getName() const;
					/// \fn getColorGetter
					/// \param {no parameters}
					Othello::Board::Pun::Colors getColor() const;
					/// \fn canPlay
					/// \param {no parameters}
					bool canPlay() const;
					/// \fn getPunCountGetter
					/// \param {no parameters}
					unsigned char getPunCount() const;

					/// \fn setCanPlaySetter
					/// \param {no parameters}
					void setCanPlay();
					/// \fn setCannotPlaySetter
					/// \param {no parameters}
					void setCannotPlay();
					/// \fn setPunCountSetter
					/// \param {punCount}
					void setPunCount( unsigned char punCount );
					/// \fn setBoardSetter
					/// \param {board}
					void setBoard( Othello::Board::GameBoard* board );

					/// \fn getMove
					/// \param {no parameters}
					virtual Othello::Board::Move getMove() = 0;
			};
		}
	}

#endif
