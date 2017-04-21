#include "inc/game.hpp"
#include "inc/board/tree/validmovenode.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;


/**
* @brief Cette fonction gère le tour d'un joueur.
* @details On commence par déterminer le joueur dont c'est le tour, puis on le commence, on l'affiche, on cherche les coups valides, on effectue le coup d'une façon ou d'une autre en fonction du joueur, puis on finit le tour et on vérifie la condition de victoire.
**/
void Game::playerTurn() { //unfolding of a turn
	if( m_currentPlayer == m_players.end() ) //those two lines set whose turn it is
		m_currentPlayer = m_players.begin();

	m_ui->playerTurnBegin( **m_currentPlayer ); //displays the game at this state.

	m_board.computeValidMoves( ( *m_currentPlayer )->getColor() );

	if( m_board.canPlay() ) {
		(*m_currentPlayer)->setCanPlay();

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
		m_ui->informNoAvailableMoves( **m_currentPlayer );
		(*m_currentPlayer)->setCannotPlay();
	}

	m_ui->playerTurnEnd( **m_currentPlayer ); //ends the turn

	verifyVictory();

	m_currentPlayer = next( m_currentPlayer ); //changes the players
}

/**
* @brief On vérifie la condition de victoire.
* @details On déclare un booleen de victoire vrai par défaut, puis on consulte le jeu actuel pour vérifier si des coups sont jouables pour l'un ou l'autre des joueurs. Si oui, le booleen devient faux
**/
void Game::verifyVictory() {
	won = true;

	for( Player*& player : m_players ) {
		if( player->canPlay() )
			won = false;
	}
}

/**
* @brief C'est la fonction de victoire. Si victoire il y a on l'execute !
* @details
**/
void Game::victory() {
	vector<Player*>::iterator winingPlayer = m_players.end();

	for( vector<Player*>::iterator iplayer = m_players.begin(); iplayer != m_players.end(); ++iplayer ) {
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

/**
* @brief fonction de preparation des joueurs.
* @details on prepare le plateau
**/
void Game::preparePlayers() {
	for( Player*& player : m_players ) {
		player->setBoard( &m_board );

		if( UIPlayer* uiplayer = dynamic_cast<UIPlayer*>( player ) ) {
			uiplayer->setUI( m_ui );
		}
	}
}

/**
* @brief Constructeur de la classe game
* @details c'est LA fonction de jeu, elle lance les tours de joueurs jusqu'à l'apparition d'une victoire. La fonction est blindée afin que le jeu se déroule correctement.
**/
Game::Game( std::vector<Player*>& players ): m_players( players ) { //that's how it goes down
	m_currentPlayer = m_players.begin(); ///first player "selected" in the vector of players passed to the constructor

	m_ui = new UI::Games::CLI( m_board, m_board.getBoard(), m_players, m_currentPlayer ); ///Here we create a User Interface

	preparePlayers(); ///call of the function "preparePlayers"

	try {
		while( !won ) //while nobody won
			playerTurn(); //turns
		victory(); //if you won -> victory
	} catch( exceptions::exit_game e ) {}

	delete m_ui; //delete UI at the end of the game
}
