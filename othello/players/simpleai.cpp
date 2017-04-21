#include "../inc/players/simpleai.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::Players;

/**
* @brief Constructeur de la classe SimpleAI
**/
SimpleAI::SimpleAI( string name, Pun::Colors color ) : Player( name, color ) {}

/**
* @brief Accesseur du mouvement pour une AI simple
* @details Cette IA retourne toujours le premier mouvement qu'elle trouve, elle joue sans but précis.
* @return le mouvement.
**/
Move SimpleAI::getMove() {
	std::random_device random_device;
	std::mt19937 engine{ random_device() };
	std::uniform_int_distribution<int> dist( 0, m_board->m_validMoves.size() - 1 );
	unsigned int i = 0, randval = dist( engine );

	for( ValidMove& validMove : m_board->m_validMoves ) {
		if( i == randval )
			return validMove;
		i++;
	}

	return ( *m_board->m_validMoves.begin() );
}
