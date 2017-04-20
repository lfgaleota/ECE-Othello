#ifndef _ECE_OTHELLO_BOARD_MOVE_HPP_
	#define _ECE_OTHELLO_BOARD_MOVE_HPP_

	#include "pun.hpp"


	/// \namespace Othello
	namespace Othello {
	    /// \namespace Board
		namespace Board {
		    /// \struct Move
			struct Move {
				const unsigned char x;
				const unsigned char y;
				const Pun::Colors color;

				/// \fn MoveOverloadConstructor
				Move( unsigned char x, unsigned char y );

				/// \fn MoveOverloadConstructorBis
				Move( unsigned char x, unsigned char y, Pun::Colors color );

				/// \fn MoveOverloadConstructorTris
				Move( const Move &move );
			};
		}
	}

	/// \fn ==OperatorOverload
	bool operator==( const Othello::Board::Move& lhs, const Othello::Board::Move& rhs );

	/// \fn <OperatorOverload
	bool operator<( const Othello::Board::Move& lhs, const Othello::Board::Move& rhs );

#endif
