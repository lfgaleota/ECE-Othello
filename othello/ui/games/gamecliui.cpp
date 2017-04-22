#include "../../inc/ui/games/gamecliui.hpp"

using namespace std;
using namespace Othello::UI::Games;
using namespace Othello::Board;
using namespace Othello::Players;

CLI::CLI( GameBoard& oboard, const GameBoard::punArray board, const vector<Player*>& players, vector<Player*>::iterator& currentPlayer ) : Game( board, players, currentPlayer ), m_oboard( oboard ) {
	cli = Functions::CLI();
	loadDisplayMatrix();
	display();
}

void CLI::showError( string msg ) {
	unsigned int width, height;
	cli.getSize( width, height );

	cli.moveCursor( height - 1, 0 );
	cli.setColor( BACKGROUND_RED );
	cout << "!";
	for( unsigned int i = 1; i < width - 7; i++ )
		cout << " ";
	cli.moveCursor( 0, 0 );

	cli.setColor( FOREGROUND_RED | FOREGROUND_INTENSITY );
	cli.moveCursor( height - 1, 1 );
	cout << msg;

	cli.resetColor();

	getchar();
}

void CLI::inform( string msg ) {
	unsigned int width, height;
	cli.getSize( width, height );

	cli.moveCursor( height - 1, 0 );
	cli.setColor( BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY );
	cout << "i";
	for( unsigned int i = 1; i < width - 7; i++ )
		cout << " ";
	cli.moveCursor( 0, 0 );

	cli.setColor( FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
	cli.moveCursor( height - 1, 1 );
	cout << msg;

	cli.resetColor();
}

void CLI::informNoAvailableMoves( Player* player ) {
	showError( "Aucun coup n'est possible pour " + player->getName() + " !" );
}

void CLI::display() {
	cli.clearScreen();
	displayMatrix();
	displayPlayers();
	displayCounts();
}

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

void CLI::highlightSelectedPiece( unsigned char x, unsigned char y, unsigned char color ) { //highlights the selected piece
	unsigned int offset_x = 0, offset_y = 0, piece_offset_x, piece_offset_y;

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

void CLI::displayCounts() {
	unsigned int width, height;

	cli.getSize( width, height );

	cli.moveCursor( height - 1, width - 7 );

	displayCount( Pun::black );
	displayCount( Pun::white );

	cli.setColor( BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY );
	cout << " ";

	cli.resetColor();
}

void CLI::displayCount( Pun::Colors color ) {
	cli.setColor( BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY );
	cout << " ";
	if( color == (*this->m_currentPlayer)->getColor() )
		cli.setColor( BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
	else
		cli.setColor( FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	cout << setw( 2 ) << (int) m_oboard.punCount( color );

	cli.resetColor();
}

Move CLI::getMove() {
	Functions::Keys::Key key;

	display();
	highlightSelectedPiece( x, y, BACKGROUND_RED ); // highlights the spot where the cursor is
	inform( "Jouez votre tour !" );

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

			case Functions::Keys::Key::N1:
				CLIValidMoveTreeViewer( m_tree, 5 );

			default:
				break;
		}

		displayMatrix();
		highlightSelectedPiece( x, y, BACKGROUND_RED );
	}

	return Move( x, y, (*m_currentPlayer)->getColor() );
}

void CLI::playerTurnBegin( Player* player ) { //the current player's turn begins --> display
	display();
}

void CLI::playerTurnEnd( Player* player ) {

}

void CLI::victory( Player* player ) {
	cli.clearScreen();

	if( player != nullptr ) {
		cout << "Le joueur " << player->getName() << " a gagné  avec " << player->getPunCount() << " pions !";
	} else {
		cout << "Draw !";
	}

	cli.getKey();
}

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

void CLI::render() {}
