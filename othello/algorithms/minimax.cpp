#include "../inc/algorithms/minimax.hpp"

using namespace std;
using namespace Othello::Algorithms;
using namespace Othello::Board;

const int MiniMax::MIN = -1000000;
const int MiniMax::DRAW = 0;
const int MiniMax::MAX = 1000000;
const int MiniMax::DEPTH = 5;

/**
* @brief Constructeur de la classe MiniMax
**/
MiniMax::MiniMax( GameBoard* ref, Othello::Board::Tree::ValidMoveNode* head, Pun::Colors color ) : m_color( color ), m_oppositeColor(  Pun::opposite( m_color ) ) {
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

	if( m_foundMove == nullptr )
		m_foundMove = &(*ref->m_validMoves.begin());
}

/**
* @brief Fonction runmax, qui lance la recherche
**/
void MiniMax::runMax( Tree::ValidMoveNode* ref, int* val ) {
	*val = max( ref, false, DEPTH );
}

/**
* @brief Fonction max.
* @details
* @return 0 (blindage) sinon return l'heuristique le min le max...
**/
int MiniMax::max( Tree::ValidMoveNode* ref, bool skipped, unsigned int depth ) {
	int minMaxVal, val;

	ref->m_board->computeValidMoves( m_color );

	if( ref->m_board->m_validMoves.size() > 0 ) {
		if( depth == 0 ) {
			return Heuristics::simple( ref->m_board, m_color );
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

		return minMaxVal;
	} else {
		if( !skipped ) {
			GameBoard* cloneBoard = new GameBoard( *ref->m_board );
			ref->m_nextNodes.push_back( Tree::ValidMoveNode( cloneBoard ) );
			std::list<Tree::ValidMoveNode>::iterator nextNode = ref->m_nextNodes.begin();
			nextNode->compute( m_oppositeColor, 1 );
			return max( &(*nextNode), true, depth );
		} else {
			GameIssue issue = ref->m_board->issue( m_color );
			if( issue == GameIssue::Victory ) {
				return MiniMax::MAX;
			}
			if( issue == GameIssue::Defeat ) {
				return MiniMax::MIN;
			}
			if( issue == GameIssue::Draw ) {
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
			return Heuristics::simple( ref->m_board, m_oppositeColor );
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

		return minMaxVal;
	} else {
		if( !skipped ) {
			GameBoard* cloneBoard = new GameBoard( *ref->m_board );
			ref->m_nextNodes.push_back( Tree::ValidMoveNode( cloneBoard ) );
			std::list<Tree::ValidMoveNode>::iterator nextNode = ref->m_nextNodes.begin();
			nextNode->compute( m_color, 1 );
			return max( &(*nextNode), true, depth );
		} else {
			GameIssue issue = ref->m_board->issue( m_color );
			if( issue == GameIssue::Victory ) {
				return MiniMax::MAX;
			}
			if( issue == GameIssue::Defeat ) {
				return MiniMax::MIN;
			}
			if( issue == GameIssue::Draw ) {
				return MiniMax::DRAW;
			}
		}
	}

	return 0;
}

/**
* @brief Accesseur de la validité du mouvement
* @return le mouvement choisi par MinMax.
**/
Othello::Board::ValidMove* MiniMax::getResult() {
	return m_foundMove;
}
