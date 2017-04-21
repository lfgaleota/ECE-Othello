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
	return Move( 0, 0 );
}
