#include "../inc/players/uiplayer.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;

UIPlayer::UIPlayer( string name, Pun::Colors color ) : Player( name, color ) {}

void UIPlayer::setUI( UI::Game *ui ) {
	m_ui = ui;
}

void UIPlayer::turnBegin() {
	m_ui->playerTurnBegin( this );
}

void UIPlayer::turnEnd() {
	m_ui->playerTurnEnd( this );
}

void UIPlayer::noAvailableMoves() {
	m_ui->informNoAvailableMoves( this );
}

void UIPlayer::error( std::string message ) {
	m_ui->showError( message );
}

UIPlayer::~UIPlayer() {}
