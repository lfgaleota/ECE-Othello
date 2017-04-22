#include "../../inc/board/tree/validmovenode.hpp"

using namespace std;
using namespace Othello::Board;

const GameBoard* Tree::ValidMoveNode::getBoard() const {
	return m_board;
}

const list<Tree::ValidMoveNode>& Tree::ValidMoveNode::getNextNodes() const {
	return m_nextNodes;
}

ValidMove* Tree::ValidMoveNode::getValidMove() const {
	return m_validMove;
}

Tree::ValidMoveNode::ValidMoveNode( GameBoard* board ) : m_board( board ) {}

Tree::ValidMoveNode::ValidMoveNode( GameBoard* board, ValidMove* validMove ) : m_board( board ), m_validMove( validMove ) {}

void Tree::ValidMoveNode::compute( Pun::Colors color, unsigned char depth ) {
	GameBoard* cloneBoard;
	Pun::Colors opposite;

	if( depth > 1 ) {
		opposite = Pun::opposite( color );
		for( ValidMove& validMove : m_board->m_validMoves ) {
			cloneBoard = new GameBoard( *m_board );
			cloneBoard->quickPlay( validMove );
			cloneBoard->computeValidMoves( opposite );
			m_nextNodes.push_back( ValidMoveNode( cloneBoard, &validMove ) );
		}
		--depth;
		for( ValidMoveNode& nextNode : m_nextNodes ) {
			nextNode.compute( opposite, depth );
		}
	} else {
		for( ValidMove& validMove : m_board->m_validMoves ) {
			cloneBoard = new GameBoard( *m_board );
			cloneBoard->quickPlay( validMove );
			m_nextNodes.push_back( ValidMoveNode( cloneBoard, &validMove ) );
		}
	}
}

void Tree::ValidMoveNode::prepareBottomStage( Pun::Colors color ) {
	Pun::Colors opposite = Pun::opposite( color );
	for( ValidMoveNode& nextNode : m_nextNodes ) {
		nextNode.m_board->computeValidMoves( opposite );
	}
}

Tree::ValidMoveNode::~ValidMoveNode() {
	for( ValidMoveNode& nextNode : m_nextNodes ) {
		delete nextNode.m_board;
	}
}

int Tree::ValidMoveNode::getEval() const {
	return m_eval;
}
