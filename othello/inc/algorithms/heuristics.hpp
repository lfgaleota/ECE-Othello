#ifndef _ECE_OTHELLO_ALGORITHMS_HEURISTICS_HPP_
	#define _ECE_OTHELLO_ALGORITHMS_HEURISTICS_HPP_

	#include "../board/gameboard.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Algorithms
		namespace Algorithms {
		    /// \class Heuristics heuristics.hpp
			class Heuristics {
				public:
				    /// \fn simple
				    /// \param {ref, color}
					static int simple( Othello::Board::GameBoard* ref, Othello::Board::Pun::Colors color );
			};
		}
	}

#endif
