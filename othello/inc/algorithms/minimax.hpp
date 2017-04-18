#ifndef _ECE_OTHELLO_ALGORITHMS_MINIMAX_HPP_
	#define _ECE_OTHELLO_ALGORITHMS_MINIMAX_HPP_

	#include <algorithm>
	#include <thread>
	#include "../board/gameboard.hpp"
	#include "../board/tree/validmovenode.hpp"
	#include "heuristics.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Algorithms
		namespace Algorithms {
		    /// \class MiniMax minimax.hpp
			class MiniMax {
				private:
					Othello::Board::ValidMove* m_foundMove = nullptr;
					Othello::Board::Pun::Colors m_color;
					//int iteration = 0;

					int max( Othello::Board::Tree::ValidMoveNode* ref, bool opposite, unsigned int depth );
					void runMax( Othello::Board::Tree::ValidMoveNode* ref, bool opposite, unsigned int depth, int* val );

				public:
					static const int MIN = -1000000;
					static const int DRAW = 0;
					static const int MAX = 1000000;
					static const int DEPTH = 5;

					/// \fn MinimaxDefaultConstructor
					MiniMax( Othello::Board::GameBoard* ref, Othello::Board::Pun::Colors color );
					/// \fn getResult
					Othello::Board::ValidMove* getResult();
			};
		}
	}

#endif
