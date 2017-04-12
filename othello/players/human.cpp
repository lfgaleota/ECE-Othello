#include "../../inc/players/human.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::Players;

Human::Human( string name, Pun::Colors color ) : Player( name, color ) {}

Move Human::getMove() {
	return m_ui->getMove();
}

void Human::setUI( Othello::UI::Game *ui ) {
	m_ui = ui;
}
