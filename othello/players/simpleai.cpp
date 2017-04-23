#include "../inc/players/simpleai.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::Players;

SimpleAI::SimpleAI( string name, Pun::Colors color ) : UIPlayer( name, color ) {}

Move SimpleAI::getMove() {
	// On récupère une nombre vraiment aléatoire entre 0 et m_board->m_validMoves.size() - 1, correspondant à l'index d'un élément de l'ensemble des coups valides
	std::random_device random_device;
	std::mt19937 engine{ random_device() };
	std::uniform_int_distribution<unsigned int> dist( 0, m_board->m_validMoves.size() - 1 );
	unsigned int i = 0, randval = dist( engine );

	// On récupère le coup valide associé à l'index
	for( ValidMove& validMove : m_board->m_validMoves ) {
		if( i == randval )
			// On retource ce coup valide trouvé
			return validMove;
		i++;
	}

	// S'il n'est pas trouvé, alors on retourne le premier coup valide pour éviter les problèmes.
	return ( *m_board->m_validMoves.begin() );
}

void SimpleAI::turnBegin() {
	UIPlayer::turnBegin();

	m_ui->inform( "L'IA réfléchit..." );
}

void SimpleAI::turnEnd() {
	UIPlayer::turnEnd();
}

Player::Type SimpleAI::getType() {
	return Player::Type::SimpleAI;
}

void SimpleAI::quit() {

}
