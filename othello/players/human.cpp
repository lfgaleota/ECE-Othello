#include "../inc/players/human.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::Players;

Human::Human( string name, Pun::Colors color ) : UIPlayer( name, color ) {}

Move Human::getMove() {
	return m_ui->getMove();
}