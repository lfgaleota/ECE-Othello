#include "../../inc/players/human.hpp"

Human::Human( std::string name, Pun::Colors color ) : Player( name, color ) {}

Move Human::getMove() {
	return m_ui->getMove();
}

void Human::setUI( Othello::UI::Game *ui ) {
	m_ui = ui;
}
