#ifndef _ECE_OTHELLO_ALGORITHMS_MINIMAX_HPP_
	#define _ECE_OTHELLO_ALGORITHMS_MINIMAX_HPP_

	#include <algorithm>
	#include <thread>
	#include "../board/gameboard.hpp"
	#include "../board/tree/validmovenode.hpp"
	#include "heuristics.hpp"

	namespace Othello {
		namespace Algorithms {
			class MiniMax {
				private:
					Othello::Board::ValidMove* m_foundMove = nullptr;
					Othello::Board::Pun::Colors m_color;
					int iteration = 0;

					int max( Othello::Board::Tree::ValidMoveNode* ref, bool opposite, bool skipped, unsigned int depth );
					void runMax( Othello::Board::Tree::ValidMoveNode* ref, int* val );

				public:
					static const int MIN;
					static const int DRAW;
					static const int MAX;
					static const int DEPTH;

					MiniMax( Othello::Board::GameBoard* ref, Othello::Board::Pun::Colors color );
					Othello::Board::ValidMove* getResult();
			};
		}
	}

#endif
