#include "inc/game.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;

void Game::playerTurn() { //unfolding of a turn
	if( m_currentPlayer == m_players.end() ) //those two lines set whose turn it is
		m_currentPlayer = m_players.begin();

	// Sauvegarde de la partie
	try {
		Othello::Save::SaveManager::save( m_board, m_players, m_currentPlayer );
	} catch( exceptions::invalid_save e ) {
		m_ui->showError( "Impossible de sauvegarder la partie." );
	}

	(*m_currentPlayer)->turnBegin(); //displays the game at this state.

	m_board->computeValidMoves( ( *m_currentPlayer )->getColor() );

	if( m_board->canPlay() ) {
		(*m_currentPlayer)->setCanPlay();

		for( bool loop = true; loop; ) {
			loop = false;

			try {
				Move move = (*m_currentPlayer)->getMove();
				m_board->play( move );
			} catch( exceptions::invalid_move& e ) {
				(*m_currentPlayer)->error( e.what() );
				loop = true;
			}
		}
	} else {
		(*m_currentPlayer)->noAvailableMoves();
		(*m_currentPlayer)->setCannotPlay();
	}

	(*m_currentPlayer)->turnEnd(); //ends the turn

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

	for( vector<Player*>::iterator iplayer = m_players.begin(); iplayer != m_players.end(); ++iplayer ) {
		(*iplayer)->setPunCount( m_board->punCount( (*iplayer)->getColor() ) );

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
	// Pour chaque joueur, on lui passe le plateau de jeu et l'interface si nécessaire.
	for( vector<Player*>::iterator iplayer = m_players.begin(); iplayer != m_players.end(); ++iplayer ) {
		(*iplayer)->setBoard( m_board );

		if( UIPlayer* uiplayer = dynamic_cast<UIPlayer*>( *iplayer ) ) {
			uiplayer->setUI( m_ui );
		}
	}
}

void Game::findStartingPlayer() {
	// On initialise le joueur actuel comme étant la fin du vecteur. Utile pour la vérification plus bas.
	m_currentPlayer = m_players.end();

	// Pour chaque joueur, on lui passe le plateau de jeu et l'interface si nécessaire.
	for( vector<Player*>::iterator iplayer = m_players.begin(); iplayer != m_players.end(); ++iplayer ) {
		// Le joueur qui commence est celui qui a des pions noirs.
		if( (*iplayer)->getColor() == Pun::black )
			m_currentPlayer = iplayer;
	}

	// Si on n'a pas trouvé de premier joueur (=joueur avec des pions noirs), on quitte: le jeu ne peut pas se dérouler correctement.
	if( m_currentPlayer == m_players.end() )
		throw logic_error( "No player with black puns. Game can not continue in this state." );
}

void Game::findStartingPlayer( unsigned char currentPlayer ) {
	unsigned char i = 0;

	// On initialise le joueur actuel comme étant la fin du vecteur. Utile pour la vérification plus bas.
	m_currentPlayer = m_players.end();

	// Pour chaque joueur, on lui passe le plateau de jeu et l'interface si nécessaire.
	for( vector<Player*>::iterator iplayer = m_players.begin(); iplayer != m_players.end(); ++iplayer ) {
		// Le joueur qui commence est celui qui est demandé.
		if( i == currentPlayer )
			m_currentPlayer = iplayer;
		i++;
	}

	// Si on n'a pas trouvé de premier joueur, on quitte: le jeu ne peut pas se dérouler correctement.
	if( m_currentPlayer == m_players.end() )
		throw logic_error( "Invalid requested current player. Corrupted save." );
}

Game::Game( std::vector<Player*>& players, bool allegro ): m_players( players ) {
	// On créé un nouveau plateau
	m_board = new GameBoard();

	findStartingPlayer();

	// On créé l'interface de jeu
	if( allegro )
		m_ui = new UI::Games::Allegro( *m_board, m_board->getBoard(), m_players, m_currentPlayer );
	else
		m_ui = new UI::Games::CLI( *m_board, m_board->getBoard(), m_players, m_currentPlayer );

	preparePlayers();

	try {
		while( !won )
			playerTurn();
		victory();
	} catch( exceptions::exit_game e ) {}

	for( vector<Player*>::iterator iplayer = m_players.begin(); iplayer != m_players.end(); ++iplayer ) {
		(*iplayer)->quit();
	}

	delete m_ui;
	delete m_board;
}

Game::Game( bool allegro ) {
	// On charge la partie
	try {
		Save::Save save = Save::SaveManager::load();
		m_board = new GameBoard( save );
		m_players = save.players;
		findStartingPlayer( save.currentPlayer );
		if( allegro )
			m_ui = new UI::Games::Allegro( *m_board, m_board->getBoard(), m_players, m_currentPlayer );
		else
			m_ui = new UI::Games::CLI( *m_board, m_board->getBoard(), m_players, m_currentPlayer );
		preparePlayers();
	} catch( exceptions::invalid_save e ) {
		throw logic_error( "Corrupted save." );
	}

	try {
		while( !won )
			playerTurn();
		victory();
	} catch( exceptions::exit_game e ) {}

	delete m_ui;
	delete m_board;

	for( Othello::Players::Player* player : m_players ) {
		delete player;
	}
}
