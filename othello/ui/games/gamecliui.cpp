#include <fstream>

#include "../../inc/ui/games/gamecliui.hpp"

using namespace std;
using namespace Othello::UI::Games;
using namespace Othello::Board;
using namespace Othello::Players;

/**
 * @brief Constructeur de l'interface de jeu
 * @details Initialise l'interface de jeu, lorsqu'il démarre.
 * @param[in] oboard Référence vers la classe #Board de jeu
 * @param[in] board Pointeur vers le plateau de jeu
 * @param[in] players Référence vers l'ensemble des joueurs
 * @param[in] currentPlayer Référence vers le joueur actuel
 */
CLI::CLI( GameBoard& oboard, const GameBoard::punArray board, const vector<Player*>& players, vector<Player*>::iterator& currentPlayer ) : Game( board, players, currentPlayer ), m_oboard( oboard ) {
	cli = Functions::CLI();
	loadDisplayMatrix();
	display();
}

/**
 * @brief Destructeur de l'interface de jeu
 * @details Nettoie l'ensemble de l'interface à la fin du jeu.
 */
CLI::~CLI() {

}

/**
 * @brief Affichage d'un erreur
 * @details Informe l'utilisateur d'une erreur au sein du programme.
 * @param msg Message d'erreur
 */
void CLI::showError( string msg ) {
	cerr << msg << endl;
}

/**
 * @brief	Affichage de l'interface
 * @details	Affiche l'ensemble de l'interface, plateau et informations des joueurs.
 */
void CLI::display() {
	cli.clearScreen(); //first erases all previous displays
#ifndef SIMPLE_UI
	displayMatrix(); //then displays the matrix
	displayPlayers(); //then displays the players
#else
	Pun::Colors color;
	for( unsigned int j = 0; j < GameBoard::sizeEdge; j++ ) {
		cout << j;
	}
	cout << endl;
	for( unsigned int j = 0; j < GameBoard::sizeEdge; j++ ) {
		for( unsigned int i = 0; i < GameBoard::sizeEdge; i++ ) {
			color = m_board[ i ][ j ];
			if( color == Pun::white )
				cout << "W";
			else if( color == Pun::black )
				cout << "B";
			else
				cout << " ";
		}
		cout << j << endl;
	}

	cout << "Tour de: " << (*m_currentPlayer)->getName() << endl;
#endif
}

/**
 * @brief	Affichage d'une pièce
 * @details	Affiche une pièce du plateau
 * @param[in] piece Pièce à afficher
 * @param[in] offsetX Coordonnée en abscisse de l'endroit où doit être affiché la pièce
 * @param[in] offsetY Coordonnée en ordonnée de l'endroit où doit être affiché la pièce
 */
void CLI::showPiece( Pun::Colors piece, unsigned int offsetX, unsigned int offsetY ) {
	if( piece != Pun::blank ) {
		if( piece == Pun::white )
			cli.setColor( BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
		else if( piece == Pun::black )
			cli.setColor( 0 );

		cout << "  ";
		cli.moveCursor( offsetY + 1, offsetX );
		cout << "  ";
	}
}

/**
 * @brief	Affichage du plateau
 * @details	Affiche le plateau de jeu à l'écran, avec le fond précalculé.
 */
void CLI::displayMatrix() {
	Pun::Colors piece;
	unsigned int offset_x = 0, offset_y = 0, piece_offset_x, piece_offset_y; //useful variables

	cli.setOffsets( this->m_displayMatrix.begin()->size(), this->m_displayMatrix.size(), offset_x, offset_y ); //places the cursor at the right spot

	for( unsigned int j = 0; j < this->m_displayMatrix.size(); j++ ) { //browse the matrix and displays the right "thing"
		cli.moveCursor( offset_y + j, offset_x );
		cli.setColor( BACKGROUND_GREEN );
		cout << m_displayMatrix[ j ];
	}

	cli.resetColor();

	for( unsigned int j = 0; j < GameBoard::sizeEdge; j++ ) { //browse again
		for( unsigned int i = 0; i < GameBoard::sizeEdge; i++ ) {
			piece = m_board[ i ][ j ];

			piece_offset_y = offset_y + j * 2 + 4;
			piece_offset_x = offset_x + i * 5 + 2;
			cli.moveCursor( piece_offset_y, piece_offset_x );

			showPiece( piece, piece_offset_x, piece_offset_y );
		}
	}

	cli.resetColor();//reset the colors, so everything can go back to normal

	// On met en surbrillance les coups valides
	for( const ValidMove& validMove : m_oboard.getValidMoves() ) {
		highlightSelectedPiece( validMove.x, validMove.y, BACKGROUND_RED | BACKGROUND_GREEN );
	}
}

/**
 * @brief	Met en valeur une pièce
 * @details	Permet de mettre en valeur un emplacement du plateau aux coordonnées indiquées, avec la couleur fournie.
 * @param[in] x Coordonnée en abscisse de l'emplacement
 * @param[in] y Coordonnée en ordonnée de l'emplacement
 * @param[in] color Couleur de surimpression
 */
void CLI::highlightSelectedPiece( unsigned char x, unsigned char y, unsigned char color ) { //highlights the selected piece
	unsigned int i, j, offset_x = 0, offset_y = 0, piece_offset_x, piece_offset_y;

	cli.setColor( color );

	cli.setOffsets( this->m_displayMatrix.begin()->size(), this->m_displayMatrix.size(), offset_x, offset_y );
	cli.setColor( color );
	cli.moveCursor( offset_y + y * 2 + 4, offset_x + x * 5 );
	cout << "|    |";
	cli.moveCursor( offset_y + y * 2 + 5, offset_x + x * 5 );
	cout << "|____|";
	//this is the adjustments in the matrix before any display

	piece_offset_y = offset_y + y * 2 + 4;
	piece_offset_x = offset_x + x * 5 + 2;
	cli.moveCursor( piece_offset_y, piece_offset_x );
	showPiece( this->m_board[ x ][ y ], piece_offset_x, piece_offset_y );

	cli.resetColor(); //reset the colors, so everything can go back to normal
}

/**
 * @brief	Affichage des joueurs
 * @details	Affiche les informations des joueurs à l'écran. Ici, leur nom est affiché, et le nom du joueur actuel est affiché en surimpression.
 */
void CLI::displayPlayers() {
	unsigned int width, height;

	cli.getSize( width, height ); //sets the size of the window and guesses the coordinates where to display everything accordingly

	cli.setColor( BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN ); //set the colors as we want them
	if( this->m_currentPlayer == this->m_players.begin() ) //initiate the current player
		cli.moveCursor( 0, 0 );
	else
		cli.moveCursor( 0, width / 2 );
	for( unsigned int i = 0; i < width / 2; i++ )
		cout << " ";
	cli.resetColor(); //reset the colors, so everything can go back to normal

	for( unsigned int i = 0; i < this->m_players.size(); i++ ) {
		cli.moveCursor( 0, ( !( i % 2 ) ? 1 : width / 2 + 1 ) );
		if( &this->m_players[ i ] == &( *this->m_currentPlayer ) )
			cli.setColor( BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
		cout << this->m_players[ i ]->getName();
		cli.resetColor(); //reset the colors, so everything can go back to normal
	}
}

/**
 * @brief	Évènement demande de coup
 * @details	Fonction appelée lorsque le jeu a besoin du coup voulu par le joueur humain. Propose également au joueur de quitter la partie, étant donné que cet écran est celui sur lequel le joueur sera la plupart du temps.
 * @return	Coup joué/demandé par le joueur
 */
Move CLI::getMove() {
	Functions::Keys::Key key;
	unsigned char x = 0, y = 0;

#ifndef SIMPLE_UI
	display();
	highlightSelectedPiece( x, y, BACKGROUND_RED ); // highlights the spot where the cursor is

	for( bool loop = true; loop; ) {
		key = cli.getKey(); //gets the use entry choice

		switch( key ) {
			case Functions::Keys::Key::ArrowUp:
				if( y > 0 )
					y--;
				break;

			case Functions::Keys::Key::ArrowDown:
				if( y < GameBoard::sizeEdge - 1 )
					y++;
				break;

			case Functions::Keys::Key::ArrowLeft:
				if( x > 0 )
					x--;
				break;

			case Functions::Keys::Key::ArrowRight:
				if( x < GameBoard::sizeEdge - 1 )
					x++;
				break;

			case Functions::Keys::Key::Enter:
				loop = false;
				break;

			case Functions::Keys::Key::N0:
			case Functions::Keys::Key::Escape:
				pauseMenu();

			default:
				break;
		}

		display(); //redo the display of the game
		highlightSelectedPiece( x, y, BACKGROUND_RED ); //highlights the cursor spot
	}

	return Move( x, y, (*m_currentPlayer)->getColor() );
#else
	cout << "Ou placer (X) ?";
	cin >> x;
	cout << "Ou placer (Y) ?";
	cin >> y;

	return Move( x - 48, y - 48, (*m_currentPlayer)->getColor() );
#endif
}

/**
 * @brief	Évènement début de tour
 * @details	Fonction appelée au début du tour d'un joueur, avant toute chose.
 * @param[in] player Joueur actuel
 */
void CLI::playerTurnBegin( Player& player ) { //the current player's turn begins --> display
	display();
}

/**
 * @brief	Évènement fin de tour
 * @details	Fonction appelée à la fin du tour d'un joueur, après toutes ses actions.
 * @param[in] player Joueur actuel
 */
void CLI::playerTurnEnd( Player& player ) {

}

/**
 * @brief	Écran de victoire
 * @details	Affiche un écran de victoire pour le joueur gagnant.
 * @param[in] player Joueur gagnant
 */
void CLI::victory( Player& player ) {
	cli.clearScreen();

	cli.getKey();
}

/**
 * @brief	Génération d'un fond de plateau
 * @details	Construit, à partir de la taille de la matrice, un fond de plateau destiné à être affiché par l'interface.
 *         	Cetet fonction ne prend et renvoie rien. Elle utilise, en revanche, le paramètre sizeEdge de #Board, et remplie l'attribut #m_displaymatrix avec un ensemble de chaînes de caractères prêtes à afficher.
 */
void CLI::loadDisplayMatrix() {
	std::string tmp;
	std::ostringstream tmp2;

	tmp = " ";
	for( unsigned int i = 0; i < GameBoard::sizeEdge - 1; i++ )
		tmp += "_____";
	tmp += "____        ";
	this->m_displayMatrix.push_back( tmp );

	tmp = "";
	for( unsigned int i = 0; i < GameBoard::sizeEdge; i++ ) {
		tmp += "| ";
		tmp += ( char ) ( 'A' + i );
		tmp += "  ";
	}
	tmp += "|       ";
	this->m_displayMatrix.push_back( tmp );

	tmp = "";
	for( unsigned int i = 0; i < GameBoard::sizeEdge; i++ ) {
		tmp += "|____";
	}
	tmp += "|       ";
	this->m_displayMatrix.push_back( tmp );

	tmp = " ";
	for( unsigned int i = 0; i < GameBoard::sizeEdge - 1; i++ ) {
		tmp += "_____";
	}
	tmp += "____   ____ ";
	this->m_displayMatrix.push_back( tmp );

	for( unsigned int j = 0; j < GameBoard::sizeEdge * 2; j++ ) {
		tmp2.str( "" );
		for( unsigned int i = 0; i < GameBoard::sizeEdge; i++ ) {
			tmp2 << "|";

			if( !( j % 2 ) ) {
				tmp2 << "    ";
			} else {
				tmp2 << "____";
			}
		}
		tmp2 << "| |";
		if( !( j % 2 ) ) {
			tmp2 << " " << j / 2 + 1 << "  |";
		} else {
			tmp2 << "____|";
		}
		this->m_displayMatrix.push_back( tmp2.str() );
	}
}

/**
 * @brief Écran de pause
 * @details Demande au joueur s'il souahite arrếter la partie. Lance une exception exit_game (cf #Exceptions) lorsque le joueur souhaite quitter le jeu.
 */
void CLI::pauseMenu() {
	vector<string> choices( { "Continuer", "Quitter" } );
	Functions::CLIs::Menu menu = Functions::CLIs::Menu( "Pause", choices, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY );
	switch( menu.getChoice() ) {
		case 2:
			// Quitter
			throw exceptions::exit_game();
		default:
			break;
	}
}
