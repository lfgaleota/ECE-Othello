#include "../inc/algorithms/minimax.hpp"

using namespace std;
using namespace Othello::Algorithms;
using namespace Othello::Board;

const int MiniMax::MIN = -1000000;
const int MiniMax::DRAW = 0;
const int MiniMax::MAX = 1000000;
const int MiniMax::DEPTH = 5;

MiniMax::MiniMax( GameBoard* ref, Othello::Board::Tree::ValidMoveNode* head, Pun::Colors color, Heuristics::evalFunctionType evalFn ) : m_color( color ), m_oppositeColor(  Pun::opposite( m_color ) ), m_evalFn( evalFn ) {
	head->compute( m_color, 1 );

	size_t nodeSize = head->m_nextNodes.size();
	unsigned int currentNode = 0;
	int moveVal = MIN;

	std::vector<int> vals( nodeSize, MIN );
	std::vector<ValidMove*> moves( nodeSize, nullptr );
	std::vector<thread*> threads( nodeSize, nullptr );

	for( Tree::ValidMoveNode& nextNode : head->m_nextNodes ) {
		moves[ currentNode ] = nextNode.m_validMove;
		threads[ currentNode ] = new thread( &MiniMax::runMax, this, &nextNode, &vals[ currentNode ] );

		currentNode++;
	}

	for( thread* th : threads ) {
		th->join();
		delete th;
	}

	for( unsigned int i = 0; i < nodeSize; i++ ) {
		if( vals[ i ] > moveVal ) {
			moveVal = vals[ i ];
			m_foundMove = moves[ i ];
		}
	}

	head->m_eval = moveVal;

	if( m_foundMove == nullptr )
		m_foundMove = &(*ref->m_validMoves.begin());
}

void MiniMax::runMax( Tree::ValidMoveNode* ref, int* val ) {
	*val = max( ref, false, DEPTH );
}

int MiniMax::max( Tree::ValidMoveNode* ref, bool skipped, unsigned int depth ) {
	int minMaxVal, val;

	ref->m_board->computeValidMoves( m_color );

	if( ref->m_board->m_validMoves.size() > 0 ) {
		if( depth == 0 ) {
			val = (*m_evalFn)( ref->m_board, m_color, m_oppositeColor );
			ref->m_eval = val;
			return val;
		}

		ref->compute( m_oppositeColor, 1 );

		--depth;

		minMaxVal = MiniMax::MIN;

		for( Tree::ValidMoveNode& nextNode : ref->m_nextNodes ) {
			val = min( &nextNode, false, depth );

			if( val > minMaxVal ) {
				minMaxVal = val;
			}
		}

		ref->m_eval = minMaxVal;

		return minMaxVal;
	} else {
		if( !skipped ) {
			GameBoard* cloneBoard = new GameBoard( *ref->m_board );
			ref->m_nextNodes.push_back( Tree::ValidMoveNode( cloneBoard ) );
			std::list<Tree::ValidMoveNode>::iterator nextNode = ref->m_nextNodes.begin();
			nextNode->compute( m_oppositeColor, 1 );

			minMaxVal = min( &(*nextNode), true, depth );
			ref->m_eval = minMaxVal;
			return minMaxVal;
		} else {
			GameIssue issue = ref->m_board->issue( m_color );
			if( issue == GameIssue::Victory ) {
				ref->m_eval = MiniMax::MAX;
				return MiniMax::MAX;
			}
			if( issue == GameIssue::Defeat ) {
				ref->m_eval = MiniMax::MIN;
				return MiniMax::MIN;
			}
			if( issue == GameIssue::Draw ) {
				ref->m_eval = MiniMax::DRAW;
				return MiniMax::DRAW;
			}
		}
	}

	return 0;
}

int MiniMax::min( Tree::ValidMoveNode* ref, bool skipped, unsigned int depth ) {
	int minMaxVal, val;

	ref->m_board->computeValidMoves( m_oppositeColor );

	if( ref->m_board->m_validMoves.size() > 0 ) {
		if( depth == 0 ) {
			val = (*m_evalFn)( ref->m_board, m_oppositeColor, m_color );
			ref->m_eval = val;
			return val;
		}

		ref->compute( m_color, 1 );

		--depth;

			minMaxVal = MiniMax::MAX;

		for( Tree::ValidMoveNode& nextNode : ref->m_nextNodes ) {
			val = max( &nextNode, false, depth );

			if( val < minMaxVal ) {
				minMaxVal = val;
			}
		}

		ref->m_eval = minMaxVal;

		return minMaxVal;
	} else {
		if( !skipped ) {
			GameBoard* cloneBoard = new GameBoard( *ref->m_board );
			ref->m_nextNodes.push_back( Tree::ValidMoveNode( cloneBoard ) );
			std::list<Tree::ValidMoveNode>::iterator nextNode = ref->m_nextNodes.begin();
			nextNode->compute( m_color, 1 );

			minMaxVal = max( &(*nextNode), true, depth );
			ref->m_eval = minMaxVal;
			return minMaxVal;
		} else {
			GameIssue issue = ref->m_board->issue( m_color );
			if( issue == GameIssue::Victory ) {
				ref->m_eval = MiniMax::MAX;
				return MiniMax::MAX;
			}
			if( issue == GameIssue::Defeat ) {
				ref->m_eval = MiniMax::MIN;
				return MiniMax::MIN;
			}
			if( issue == GameIssue::Draw ) {
				ref->m_eval = MiniMax::DRAW;
				return MiniMax::DRAW;
			}
		}
	}

	return 0;
}

Othello::Board::ValidMove* MiniMax::getResult() {
	return m_foundMove;
}
