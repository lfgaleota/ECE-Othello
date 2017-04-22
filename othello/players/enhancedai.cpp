#include "../inc/players/enhancedai.hpp"

using namespace std;
using namespace Othello::Algorithms;
using namespace Othello::Board;
using namespace Othello::Players;

/**
* @brief Constructeur de la classe EnhancedAI
**/
EnhancedAI::EnhancedAI( string name, Pun::Colors color ) : UIPlayer( name, color ), m_tree( nullptr ) {}

/**
* @brief Accesseur du mouvement pour une AI simple
* @details Cette IA récupère le mouvement voulu en appelant la fonction qui contient l'algorithme de minmax.
* @return le mouvement.
**/
Move EnhancedAI::getMove() {
	m_ui->inform( "L'IA reflechit..." );

	m_tree = Tree::ValidMoveNode( m_board );
	m_ui->setTree( &m_tree );

	MiniMax minimax( m_board, &m_tree, m_color );

	ValidMove* move = minimax.getResult();
	if( move == nullptr )
		throw logic_error( "Move not found" );
	return *move;
}
