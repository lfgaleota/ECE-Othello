#ifndef _ECE_OTHELLO_BOARD_DIRECTIONVECTOR_HPP_
	#define _ECE_OTHELLO_BOARD_DIRECTIONVECTOR_HPP_

	#include <list>

	namespace Othello {
		namespace Board {
			struct DirectionVector {
				const char x;
				const char y;

				DirectionVector( char direction_x, char direction_y );

				const static std::list<DirectionVector> directions;
			};
		}
	}

	bool const operator==( Othello::Board::DirectionVector& lhs, Othello::Board::DirectionVector& rhs );

#endif
