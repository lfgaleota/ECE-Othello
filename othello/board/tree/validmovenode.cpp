#include "../../inc/board/tree/validmovenode.hpp"

using namespace std;
using namespace Othello::Board;

const GameBoard* Tree::ValidMoveNode::getBoard() const {
	return m_board;
}

const list<Tree::ValidMoveNode>& Tree::ValidMoveNode::getNextNodes() const {
	return m_nextNodes;
}

Tree::ValidMoveNode::ValidMoveNode( GameBoard* board ) : m_board( board ) {}

void Tree::ValidMoveNode::compute( Pun::Colors color, unsigned char depth ) {
	GameBoard* cloneBoard;
	Pun::Colors opposite;

	if( depth >= 0 ) {
		opposite = Pun::opposite( color );
		for( const ValidMove& validMove : m_board->m_validMoves ) {
			cloneBoard = new GameBoard( *m_board );
			cloneBoard->quickPlay( validMove );
			cloneBoard->computeValidMoves( opposite );
			m_nextNodes.push_back( ValidMoveNode( cloneBoard ) );
		}
		if( depth > 1 ) {
			--depth;
			for( ValidMoveNode& nextNode : m_nextNodes ) {
				nextNode.compute( opposite, depth );
			}
		}
	}
}

Tree::ValidMoveNode::~ValidMoveNode() {
	for( ValidMoveNode& nextNode : m_nextNodes ) {
		delete nextNode.m_board;
	}
}
