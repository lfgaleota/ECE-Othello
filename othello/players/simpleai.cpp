#include "../inc/players/simpleai.hpp"

using namespace std;
using namespace Othello::Algorithms;
using namespace Othello::Board;
using namespace Othello::Players;

SimpleAI::SimpleAI( string name, Pun::Colors color ) : UIPlayer( name, color ), m_tree( nullptr ) {
	m_done = false;
}

Move SimpleAI::getMove() {
	m_done = false;
	m_tree = Tree::ValidMoveNode( m_board );

	th = thread( &SimpleAI::run, this );

	for( ;; ) {
		m_ui->render();

		this_thread::sleep_for( chrono::milliseconds( 33 ) );

		if( m_done ) {
			th.join();
			m_ui->setTree( &m_tree );
			return *m_move;
		}
	}
}

void SimpleAI::turnBegin() {
	UIPlayer::turnBegin();

	m_ui->inform( "L'IA reflechit..." );
}

void SimpleAI::turnEnd() {
	UIPlayer::turnEnd();
}

Player::Type SimpleAI::getType() {
	return Player::Type::SimpleAI;
}

void SimpleAI::run() {
	AlphaBeta alphabeta( m_board, &m_tree, m_color, &Heuristics::simple );
	m_move = alphabeta.getResult();
	if( m_move == nullptr )
		throw logic_error( "Move not found" );
	m_done = true;
}

void SimpleAI::quit() {
	if( th.joinable() )
		th.join();
}
