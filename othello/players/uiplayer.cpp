#include "../inc/players/uiplayer.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;

UIPlayer::UIPlayer( string name, Pun::Colors color ) : Player( name, color ) {

}

void UIPlayer::setUI( UI::Game *ui ) {
	m_ui = ui;
}
