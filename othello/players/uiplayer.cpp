#include "../inc/players/uiplayer.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;

/**
* @brief Constructeur de la classe UIPlayer
**/
UIPlayer::UIPlayer( string name, Pun::Colors color ) : Player( name, color ) {

}

/**
* @brief Mutateur de l'UI dans la classe UIPlayer
**/
void UIPlayer::setUI( UI::Game *ui ) {
	m_ui = ui;
}
