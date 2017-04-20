#ifndef _ECE_OTHELLO_BOARD_VALIDMOVE_HPP_
	#define _ECE_OTHELLO_BOARD_VALIDMOVE_HPP_

	#include <list>
	#include "move.hpp"
	#include "direction_vector.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Board
		namespace Board {
		    /// \struct ValidMove
			struct ValidMove : public Move {
				std::list<DirectionVector> directions;

				/// \fn ValidMoveOverloadConstructor
				ValidMove( unsigned char x, unsigned char y );

				/// \fn ValideMoveOverloadConstructorBis
				ValidMove( const Move &move );

				/// \fn addDirection
				inline void addDirection( DirectionVector dvec ) {
					directions.push_back( dvec );
				}
			};
		}
	}

#endif
