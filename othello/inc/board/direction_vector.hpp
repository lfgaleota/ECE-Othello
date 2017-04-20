#ifndef _ECE_OTHELLO_BOARD_DIRECTIONVECTOR_HPP_
	#define _ECE_OTHELLO_BOARD_DIRECTIONVECTOR_HPP_

	#include <list>

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Board
		namespace Board {
		    /// \struct DirectionVector
			struct DirectionVector {
				const char x;
				const char y;

				/// \fn DirectionVectorOverloadConstructor
				/// \param {direction_x, direction_y}
				DirectionVector( char direction_x, char direction_y );
			};
		}
	}

	/// \fn ==OperatorOverload
	/// \param {direction vectors lhs and rhs}
	bool const operator==( Othello::Board::DirectionVector& lhs, Othello::Board::DirectionVector& rhs );

#endif
