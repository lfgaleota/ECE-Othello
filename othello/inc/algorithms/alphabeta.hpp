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
			class AlphaBeta {
				private:
					Othello::Board::ValidMove* m_foundMove = nullptr;
					Othello::Board::Pun::Colors m_color, m_oppositeColor;

					/// \fn max
					/// \param {ValidMoveNode, opposite, skipped, depth}
					int max( Othello::Board::Tree::ValidMoveNode* ref, int alpha, int beta, bool skipped, unsigned int depth );
					int min( Othello::Board::Tree::ValidMoveNode* ref, int alpha, int beta, bool skipped, unsigned int depth );
					/// \fn runMax
					/// \param {ValidMoveNode, val}
					void runMax( Othello::Board::Tree::ValidMoveNode* ref, int* val );

				public:
					static const int MIN;
					static const int DRAW;
					static const int MAX;
					static const int DEPTH;

					/// \fn MinimaxDefaultConstructor
					/// \param {ref, color}
					AlphaBeta( Othello::Board::GameBoard* ref, Othello::Board::Tree::ValidMoveNode* head, Othello::Board::Pun::Colors color );
					/// \fn getResult
					/// \param {No parameters}
					Othello::Board::ValidMove* getResult();
			};
		}
	}

#endif
