#ifndef _ECE_OTHELLO_BOARD_MOVE_HPP_
	#define _ECE_OTHELLO_BOARD_MOVE_HPP_

	#include "pun.hpp"


	namespace Othello {
		namespace Board {
		    /// \struct Move
			struct Move {
				const unsigned char x;
				const unsigned char y;
				const Pun::Colors color;

				Move( unsigned char x, unsigned char y );

				Move( unsigned char x, unsigned char y, Pun::Colors color );

				Move( const Move &move );
			};
		}
	}

	bool operator==( const Othello::Board::Move& lhs, const Othello::Board::Move& rhs );

	bool operator<( const Othello::Board::Move& lhs, const Othello::Board::Move& rhs );

#endif
