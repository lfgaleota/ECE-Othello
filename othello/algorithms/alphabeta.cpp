#include "../inc/algorithms/alphabeta.hpp"

using namespace std;
using namespace Othello::Algorithms;
using namespace Othello::Board;

const int AlphaBeta::MIN = -1000000;
const int AlphaBeta::DRAW = 0;
const int AlphaBeta::MAX = 1000000;
const int AlphaBeta::DEPTH = 5;

/**
* @brief Constructeur de la classe AlphaBeta
**/
AlphaBeta::AlphaBeta( GameBoard* ref, Othello::Board::Tree::ValidMoveNode* head, Pun::Colors color, Heuristics::evalFunctionType evalFn ) : m_color( color ), m_oppositeColor(  Pun::opposite( m_color ) ), m_evalFn( evalFn ) {
	head->compute( m_color, 1 );

	size_t nodeSize = head->m_nextNodes.size();
	unsigned int currentNode = 0;
	int moveVal = MIN;

	std::vector<int> vals( nodeSize, MIN );
	std::vector<ValidMove*> moves( nodeSize, nullptr );
	std::vector<thread*> threads( nodeSize, nullptr );

	for( Tree::ValidMoveNode& nextNode : head->m_nextNodes ) {
		moves[ currentNode ] = nextNode.m_validMove;
		threads[ currentNode ] = new thread( &AlphaBeta::runMax, this, &nextNode, &vals[ currentNode ] );

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

/**
* @brief Fonction runmax, qui lance la recherche
**/
void AlphaBeta::runMax( Tree::ValidMoveNode* ref, int* val ) {
	*val = max( ref, AlphaBeta::MIN, AlphaBeta::MAX, false, DEPTH );
}

/**
* @brief Fonction max.
* @details
* @return 0 (blindage) sinon return l'heuristique le min le max...
**/
int AlphaBeta::max( Tree::ValidMoveNode* ref, int alpha, int beta, bool skipped, unsigned int depth ) {
	int val;

	ref->m_board->computeValidMoves( m_color );

	if( ref->m_board->m_validMoves.size() > 0 ) {
		if( depth == 0 ) {
			val = (*m_evalFn)( ref->m_board, m_color, m_oppositeColor );
			ref->m_eval = val;
			return val;
		}

		ref->compute( m_oppositeColor, 1 );

		--depth;

		for( Tree::ValidMoveNode& nextNode : ref->m_nextNodes ) {
			val = min( &nextNode, alpha, beta, false, depth );

			if( val > alpha )
				alpha = val;
			if( alpha >= beta )
				break; // Coupe Beta
		}

		ref->m_eval = alpha;
		return alpha;
	} else {
		if( !skipped ) {
			GameBoard* cloneBoard = new GameBoard( *ref->m_board );
			ref->m_nextNodes.push_back( Tree::ValidMoveNode( cloneBoard ) );
			std::list<Tree::ValidMoveNode>::iterator nextNode = ref->m_nextNodes.begin();
			nextNode->compute( m_oppositeColor, 1 );

			val = min( &(*nextNode), alpha, beta, true, depth );
			ref->m_eval = val;
			return val;
		} else {
			GameIssue issue = ref->m_board->issue( m_color );
			if( issue == GameIssue::Victory ) {
				ref->m_eval = AlphaBeta::MAX;
				return AlphaBeta::MAX;
			}
			if( issue == GameIssue::Defeat ) {
				ref->m_eval = AlphaBeta::MIN;
				return AlphaBeta::MIN;
			}
			if( issue == GameIssue::Draw ) {
				ref->m_eval = AlphaBeta::DRAW;
				return AlphaBeta::DRAW;
			}
		}
	}

	return 0;
}

int AlphaBeta::min( Tree::ValidMoveNode* ref, int alpha, int beta, bool skipped, unsigned int depth ) {
	int val;

	ref->m_board->computeValidMoves( m_oppositeColor );

	if( ref->m_board->m_validMoves.size() > 0 ) {
		if( depth == 0 ) {
			val = (*m_evalFn)( ref->m_board, m_oppositeColor, m_color );
			ref->m_eval = val;
			return val;
		}

		ref->compute( m_color, 1 );

		--depth;

		for( Tree::ValidMoveNode& nextNode : ref->m_nextNodes ) {
			val = max( &nextNode, alpha, beta, false, depth );

			if( val < beta )
				beta = val;
			if( beta <= alpha )
				break; // Coupe Alpha
		}

		ref->m_eval = beta;
		return beta;
	} else {
		if( !skipped ) {
			GameBoard* cloneBoard = new GameBoard( *ref->m_board );
			ref->m_nextNodes.push_back( Tree::ValidMoveNode( cloneBoard ) );
			std::list<Tree::ValidMoveNode>::iterator nextNode = ref->m_nextNodes.begin();
			nextNode->compute( m_color, 1 );

			val = max( &(*nextNode), alpha, beta, true, depth );
			ref->m_eval = val;
			return val;
		} else {
			GameIssue issue = ref->m_board->issue( m_color );
			if( issue == GameIssue::Victory ) {
				ref->m_eval = AlphaBeta::MAX;
				return AlphaBeta::MAX;
			}
			if( issue == GameIssue::Defeat ) {
				ref->m_eval = AlphaBeta::MIN;
				return AlphaBeta::MIN;
			}
			if( issue == GameIssue::Draw ) {
				ref->m_eval = AlphaBeta::DRAW;
				return AlphaBeta::DRAW;
			}
		}
	}

	return 0;
}

/**
* @brief Accesseur de la validité du mouvement
* @return le mouvement choisi par MinMax.
**/
Othello::Board::ValidMove* AlphaBeta::getResult() {
	return m_foundMove;
}
