#ifndef _ECE_OTHELLO_BOARD_MOVE_HPP_
	#define _ECE_OTHELLO_BOARD_MOVE_HPP_

	#include "pun.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Board
		namespace Board {
		    /// \struct Move
		    /// \brief structure gérant le mouvement
			struct Move {
				const unsigned char x;
				const unsigned char y;
				const Pun::Colors color;

				/// \fn MoveOverloadConstructor
				/// \param {x, y}
				Move( unsigned char x, unsigned char y );

				/// \fn MoveOverloadConstructorBis
				/// \param {x, y, color}
				Move( unsigned char x, unsigned char y, Pun::Colors color );

				/// \fn MoveOverloadConstructorTris
				/// \param {move}
				Move( const Move &move );
			};
		}
	}

	/// \fn ==OperatorOverload
	/// \param {lhs, rhs}
	bool operator==( const Othello::Board::Move& lhs, const Othello::Board::Move& rhs );

	/// \fn <OperatorOverload
	/// \param {lhs, rhs}
	bool operator<( const Othello::Board::Move& lhs, const Othello::Board::Move& rhs );

#endif
