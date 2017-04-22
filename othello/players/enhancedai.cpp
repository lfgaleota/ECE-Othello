#include "../inc/players/enhancedai.hpp"

using namespace std;
using namespace Othello::Algorithms;
using namespace Othello::Board;
using namespace Othello::Players;

EnhancedAI::EnhancedAI( string name, Pun::Colors color ) : UIPlayer( name, color ), m_tree( nullptr ) {
	m_done = false;
}

Move EnhancedAI::getMove() {
	m_done = false;
	m_tree = Tree::ValidMoveNode( m_board );
	m_ui->setTree( &m_tree );

	AlphaBeta alphabeta( m_board, &m_tree, m_color );

	ValidMove* move = alphabeta.getResult();
	if( move == nullptr )
		throw logic_error( "Move not found" );
	m_done = true;
	return *move;
}

void EnhancedAI::turnBegin() {
	UIPlayer::turnBegin();

	m_ui->inform( "L'IA réfléchit..." );
}

void EnhancedAI::turnEnd() {
	UIPlayer::turnEnd();
}

Player::Type EnhancedAI::getType() {
	return Player::Type::EnhancedAI;
}
