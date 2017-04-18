#include "../inc/players/enhancedai.hpp"

using namespace std;
using namespace Othello::Algorithms;
using namespace Othello::Board;
using namespace Othello::Players;

EnhancedAI::EnhancedAI( string name, Pun::Colors color ) : UIPlayer( name, color ) {}

Move EnhancedAI::getMove() {
	m_ui->inform( "L'IA reflechit..." );

	MiniMax minimax( m_board, m_color );

	ValidMove* move = minimax.getResult();
	if( move == nullptr )
		throw logic_error( "Move not found" );
	return *move;
}
