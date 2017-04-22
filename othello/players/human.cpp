#include "../inc/players/human.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::Players;


Human::Human( string name, Pun::Colors color ) : UIPlayer( name, color ) {}

Move Human::getMove() {
	for( ;; ) {
		m_ui->render();
		try {
			return m_ui->getMove();
		} catch( exceptions::no_selected_move e ) {}
	}
}

void Human::turnBegin() {
	UIPlayer::turnBegin();
	m_ui->inform( "Jouez votre tour !" );
}

void Human::turnEnd() {
	UIPlayer::turnEnd();
}

Player::Type Human::getType() {
	return Player::Type::Human;
}
