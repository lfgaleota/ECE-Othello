#include "../inc/algorithms/minimax.hpp"

using namespace std;
using namespace Othello::Algorithms;
using namespace Othello::Board;

MiniMax::MiniMax( GameBoard* ref, Pun::Colors color ) : m_color( color ) {
	Tree::ValidMoveNode head( ref, nullptr );
	head.compute( m_color, 1 );

	size_t nodeSize = head.m_nextNodes.size();
	unsigned int currentNode = 0;
	int moveVal = -1000000;

	std::vector<int> vals( nodeSize, -1000000 );
	std::vector<ValidMove*> moves( nodeSize, nullptr );
	std::vector<thread*> threads( nodeSize, nullptr );

	for( Tree::ValidMoveNode& nextNode : head.m_nextNodes ) {
		moves[ currentNode ] = nextNode.m_validMove;
		threads[ currentNode ] = new thread( &MiniMax::runMax, this, &nextNode, false, 5, &vals[ currentNode ] );

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

void MiniMax::runMax( Tree::ValidMoveNode* ref, bool opposite, unsigned int depth, int* val ) {
	*val = max( ref, opposite, depth );
}

int MiniMax::max( Tree::ValidMoveNode* ref, bool opposite, unsigned int depth ) {
	int maxVal = MiniMax::MIN, val;
	Pun::Colors oppositeColor = Pun::opposite( m_color );

	ref->m_board->computeValidMoves( m_color );

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

	//cout << (int) depth << ": " << ++iteration << endl;

	if( depth == 0 ) {
		return Heuristics::simple( ref->m_board, m_color );
	}

	ref->compute( oppositeColor, 1 );

	--depth;

	for( Tree::ValidMoveNode& nextNode : ref->m_nextNodes ) {
		val = max( &nextNode, ~opposite, depth );

		if( val > maxVal ) {
			maxVal = val;
		}
	}
	if( opposite )
		return -maxVal;
	else
		return maxVal;
}

Othello::Board::ValidMove* MiniMax::getResult() {
	return m_foundMove;
}
