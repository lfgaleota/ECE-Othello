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

	th = thread( &EnhancedAI::run, this );

	for( ;; ) {
		m_ui->render();

		this_thread::sleep_for( chrono::milliseconds( 50 ) );

		if( m_done ) {
			th.join();
			m_ui->setTree( &m_tree );
			return *m_move;
		}
	}
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

void EnhancedAI::run() {
	AlphaBeta alphabeta( m_board, &m_tree, m_color );
	m_move = alphabeta.getResult();
	if( m_move == nullptr )
		throw logic_error( "Move not found" );
	m_done = true;
}

void EnhancedAI::quit() {
	if( th.joinable() )
		th.join();
}
