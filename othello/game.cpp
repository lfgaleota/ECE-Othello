#include "../inc/game.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;

void Game::playerTurn() { //unfolding of a turn
	if( m_currentPlayer == m_players.end() )
		m_currentPlayer = m_players.begin();

	m_ui->playerTurnBegin( **m_currentPlayer );

	m_board.computeValidMoves(( *m_currentPlayer )->getColor());

	for( bool loop = true; loop; ) {
		loop = false;

		try {
			Move move = (*m_currentPlayer)->getMove();
			m_board.play( move );
		} catch( exceptions::invalid_move& e ) { //shielding
			m_ui->showError( e.what() );
			loop = true;
		}
	}

	m_ui->playerTurnEnd( **m_currentPlayer ); //ends the turn

	m_currentPlayer = next( m_currentPlayer ); //changes the players
}

void Game::victory() { //WIN
	vector<Player*>::iterator winingPlayer = m_currentPlayer;

	m_ui->victory( **winingPlayer );
}

void Game::preparePlayers() {
	for( Player*& player : m_players ) {
		if( Human* human = dynamic_cast<Human*>( player ) ) {
			human->setUI( m_ui );
		}
	}
}

Game::Game( std::vector<Player*>& players ): m_players( players ) { //that's how it goes down
	m_currentPlayer = m_players.begin(); //first player "selected"

	m_ui = new UI::Games::CLI( m_board, m_board.getBoard(), m_players, m_currentPlayer );

	preparePlayers();

	try {
		while( !won ) //while nobody won
			playerTurn(); //turns
		victory(); //if you won -> victory
	} catch( exceptions::exit_game e ) {}

	delete m_ui;
}
