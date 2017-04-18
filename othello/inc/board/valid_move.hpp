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

				ValidMove( unsigned char x, unsigned char y );

				ValidMove( const Move &move );

				inline void addDirection( DirectionVector dvec ) {
					directions.push_back( dvec );
				}
			};
		}
	}

#endif
