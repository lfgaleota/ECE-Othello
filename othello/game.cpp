#include "inc/game.hpp"
#include "inc/board/tree/validmovenode.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;

void Game::playerTurn() { //unfolding of a turn
	if( m_currentPlayer == m_players.end() )
		m_currentPlayer = m_players.begin();

	m_ui->playerTurnBegin( **m_currentPlayer );

	m_board.computeValidMoves( ( *m_currentPlayer )->getColor() );

	if( m_board.canPlay() ) {
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
	} else {
		m_ui->showError( "Aucun coup n'est possible pour vous !" );
		(*m_currentPlayer)->setCannotPlay();
	}

	m_ui->playerTurnEnd( **m_currentPlayer ); //ends the turn

	verifyVictory();

	m_currentPlayer = next( m_currentPlayer ); //changes the players
}

void Game::verifyVictory() {
	won = true;

	for( Player*& player : m_players ) {
		if( player->canPlay() )
			won = false;
	}
}

void Game::victory() {
	vector<Player*>::iterator winingPlayer = m_players.end();

	for( vector<Player*>::iterator iplayer = m_players.begin(); iplayer != m_players.end(); next( iplayer ) ) {
		(*iplayer)->setPunCount( m_board.punCount( (*iplayer)->getColor() ) );

		if( winingPlayer != m_players.end() ) {
			if( (*iplayer)->getColor() != (*winingPlayer)->getColor() ) {
				if( (*iplayer)->getPunCount() > (*winingPlayer)->getPunCount() ) {
					winingPlayer = iplayer;
				} else if( (*iplayer)->getPunCount() == (*winingPlayer)->getPunCount() ) {
					winingPlayer = m_players.end();
				}
			}
		} else {
			winingPlayer = iplayer;
		}
	}

	if( winingPlayer == m_players.end() )
		m_ui->victory( nullptr );
	else
		m_ui->victory( *winingPlayer );
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
