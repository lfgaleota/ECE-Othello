#include <fstream>

#include "../../inc/ui/games/gamecliui.hpp"

//access via the namespaces
using namespace std;
using namespace Siam;
using namespace Siam::Objects;
using namespace Siam::Matrixs;
using namespace Siam::UI::Games;

CLI::CLI( const std::vector<std::vector<Siam::Object*>>& board, const std::vector<Siam::Player>& players, std::vector<Siam::Player>::iterator& currentPlayer, Siam::UI::Audio::FMOD& fmod ) : Game( board, players, currentPlayer, fmod ) { //overload constructor
	cli = Functions::CLI();
	this->m_fmod.playMusic( "main1" );
	loadDisplayMatrix();
	display();
}

CLI::~CLI() { //destructor
	this->m_fmod.stopMusic();
}

void CLI::showError( string msg ) { //if we need to show an error, call this
	cerr << msg << endl;
}

void CLI::display() { //Does the display when in game
	cli.clearScreen(); //first erases all previous displays
	displayMatrix(); //then displays the matrix
	displayPlayers(); //then displays the players
	displayActions(); //then displays the possible actions a play can take
}

void CLI::showPiece( Object* elem ) {
	if( elem != nullptr ) { //different types of display function of the spot content
		switch( elem->getType() ) {
			case Types::Type::Mountain: //displays the right char depends on the type of the object pointed by the spot
				cout << "M";
				break;
			case Types::Type::Rhinoceros:
				cout << "R";
				break;
			case Types::Type::Elephant:
				cout << "E";
				break;
			case Types::Type::Object:
				break;
			case Types::Type::Entity:
				break;
		}
		if( elem->getType() == Types::Type::Mountain )
			cout << " ";
		else {
			cli.setColor( FOREGROUND_BLUE | FOREGROUND_INTENSITY ); //we need to display the direction of the piece in another color
			switch( elem->getDirection() ) { //display the direction of a piece
				case Direction::Left:
					cout << "<";
					break;
				case Direction::Right:
					cout << ">";
					break;
				case Direction::Up:
					cout << "/";
					break;
				case Direction::Down:
					cout << "\\";
					break;
			}
			cli.resetColor(); //reset the colors, so everything can go back to normal
		}
	} else {
		cout << "  ";
	}
}

void CLI::displayMatrix() {
	Object* elem = nullptr; //we'll need this to fill the blank spots
	unsigned int x = 0, y = 0; //useful variables

	cli.setOffsets( this->m_displayMatrix.begin()->size(), this->m_displayMatrix.size(), x, y ); //places the cursor at the right spot

	for( unsigned int j = 0; j < this->m_displayMatrix.size(); j++ ) { //browse the matrix and displays the right "thing"
		cli.moveCursor( y + j, x );
		cli.setColor( FOREGROUND_RED | FOREGROUND_INTENSITY );
		cout << m_displayMatrix[ j ];
	}

	cli.resetColor();

	for( unsigned int j = 0; j < this->m_board.size(); j++ ) { //browse again
		for( unsigned int i = 0; i < this->m_board[ j ].size(); i++ ) {
			elem = this->m_board[ i ][ j ]; //displays the right element

			cli.moveCursor( y + j * 2 + 4, x + i * 5 + 2 );
			cli.setColor( FOREGROUND_GREEN | FOREGROUND_INTENSITY );

			showPiece( elem );
		}
	}

	cli.resetColor();//reset the colors, so everything can go back to normal
}

void CLI::highlightSelectedPiece( unsigned int x, unsigned int y, unsigned char color ) { //highlights the selected piece
	unsigned int offsetX = 0, offsetY = 0;

	cli.setColor( color );

	cli.setOffsets( this->m_displayMatrix.begin()->size(), this->m_displayMatrix.size(), offsetX, offsetY );
	cli.moveCursor( offsetY + y * 2 + 4, offsetX + x * 5 + 2 );
	//this is the adjustments in the matrix before any display

	showPiece( this->m_board[ x ][ y ] );

	cli.moveCursor( offsetY + y * 2 + 4 + 1, offsetX + x * 5 + 2 );
	cout << "__"; //displaying this along with a new background intensity show some kind of cursor

	cli.resetColor(); //reset the colors, so everything can go back to normal
}

void CLI::displayPlayers(){ //displays the players information
	std::string carac = "";
	unsigned int offset_x, offset_y, width, height, pos_y = 0;

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
		cli.moveCursor( 0, ( !( i % 2 ) ? 0 : width / 2 ) );
		if( &this->m_players[ i ] == &( *this->m_currentPlayer ) )
			cli.setColor( BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
		cout << this->m_players[ i ].getName();
		cli.resetColor(); //reset the colors, so everything can go back to normal
	}

	cli.setOffsets( 1, 5, offset_x, offset_y ); //does the sizing to display

	for( unsigned int i = 0; i < this->m_players.size(); i++ ) { //display the remaining animals of each player
		switch( this->m_players[ i ].getAnimalChosen() ) {
			case Types::Type::Elephant:
				cli.setColor( BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
				carac = "E";
				break;
			case Types::Type::Rhinoceros:
				cli.setColor( BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
				carac = "R";
				break;
			default:
				throw exceptions::invalid_object_type();
		}

		if( i == 0 )
			pos_y = 1;
		else
			pos_y = width - 2;

		for( unsigned int j = 0; j < this->m_players[ i ].getRemainingObjects(); j++ ) {
			cli.moveCursor( offset_y + j, pos_y );
			std::cout << carac;
		}

		cli.resetColor(); //reset the colors, so everything can go back to normal
	}
}

void CLI::displayActions() {
	unsigned int width, height; //useful variables
	string menu[] = { // menu choices
			"Ajouter",
			"Retirer",
			"Deplacer",
			"Orienter",
			"Passer"
	};
	if( this->m_showActions ){ //shows the menu
		cli.getSize( width, height );

		cli.moveCursor( height - 1, 0 );
		for( unsigned int i = 0; i < 5; i++ ) {
			cli.setColor( BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY ); //right colors
			cout << i + 1;
			cli.setColor( BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN );
			cout << menu[ i ];
		}

		cli.setColor( BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY );
		cout << 0;
		cli.setColor( BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN );
		cout << "Quitter";

		cli.resetColor(); //reset the colors, so everything can go back to normal
	}
}

void CLI::getPlayerCoords( unsigned int& x, unsigned int& y, Direction* dir ) { //gets the player coordinates in ordor to display the right thing
	Functions::Keys::Key key;
	x = 0;
	y = 0;

	this->m_showActions = false; //we don't show the actions anymore

	display();
	highlightSelectedPiece( x, y ); // highlights the spot where the cursor is

	for( bool loop = true; loop; ) {
		key = cli.getKey(); //gets the use entry choice

		switch( key ) {
			case Functions::Keys::Key::ArrowUp:
				if( y > 0 )
					y--;
				break;

			case Functions::Keys::Key::ArrowDown:
				if( y < this->m_board.size() - 1 )
					y++;
				break;

			case Functions::Keys::Key::ArrowLeft:
				if( x > 0 )
					x--;
				break;

			case Functions::Keys::Key::ArrowRight:
				if( x < this->m_board.begin()->size() - 1 )
					x++;
				break;

			case Functions::Keys::Key::Enter:
				loop = false;
				break;

			case Functions::Keys::Key::N0:
			case Functions::Keys::Key::Escape:
				this->m_showActions = true;
				display();
				throw exceptions::cancel_action();

			default:
				break;
		}

		display(); //redo the display of the game
		highlightSelectedPiece( x, y ); //highlights the cursor spot
	}

	if( dir != nullptr ) {
		for( bool loop = true; loop; ) {
			loop = false;
			display();

			if( x < this->m_board.begin()->size() - 1 )
				highlightSelectedPiece( x + 1, y, BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE |
				                                  FOREGROUND_GREEN | FOREGROUND_INTENSITY );
			if( x > 0 )
				highlightSelectedPiece( x - 1, y, BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE |
				                                  FOREGROUND_GREEN | FOREGROUND_INTENSITY );
			if( y < this->m_board.size() - 1 )
				highlightSelectedPiece( x, y + 1, BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE |
				                                  FOREGROUND_GREEN | FOREGROUND_INTENSITY );
			if( y > 0 )
				highlightSelectedPiece( x, y - 1, BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE |
				                                  FOREGROUND_GREEN | FOREGROUND_INTENSITY );

			key = cli.getKey(); //get the key again to choose direction

			switch( key ) {
				case Functions::Keys::Key::ArrowLeft: //each arrow has its direction associated
					*dir = Direction::Left;
					break;

				case Functions::Keys::Key::ArrowRight:
					*dir = Direction::Right;
					break;

				case Functions::Keys::Key::ArrowUp:
					*dir = Direction::Up;
					break;

				case Functions::Keys::Key::ArrowDown:
					*dir = Direction::Down;
					break;

				case Functions::Keys::Key::N0:
				case Functions::Keys::Key::Escape:
					this->m_showActions = true; //make the display changes
					display(); //display everything again
					throw exceptions::cancel_action(); //shielding

				default:
					loop = true;
					break;
			}
		}
	}

	this->m_showActions = true;
}

void CLI::addPiece( const Object*, unsigned int x, unsigned int y ) { //add a piece on the board --> display
	display();
}

void CLI::removePiece( const Object* ) { //removes a piece on the board --> display
	display();
}

void CLI::movePiece( map<const Object*, pair<unsigned int, unsigned int>>& movements ) { //moves a piece on the board --> display
	display();
}

void CLI::orientPiece( const Object* ) { //orients a piece on the board --> display
	display();
}

void CLI::ejectPiece( const Object* ) { //ejects a piece from the board --> display

}

void CLI::playerTurnBegin( Siam::Player& player ) { //the current player's turn begins --> display
	display();
}

void CLI::playerTurnEnd( Siam::Player& player ) { //the current player's turn ends --> display

}

Players::Action CLI::getPlayerAction( Siam::Player& player ) { //allows the get the action choice of the player
	Functions::Keys::Key key;

	while( true ) {
		key = cli.getKey(); //gets user's entry

		switch( key ) { //what type of turn would you like to take ?
			case Functions::Keys::Key::N1:
				return Players::Action::Add;
			case Functions::Keys::Key::N2:
				return Players::Action::Remove;
			case Functions::Keys::Key::N3:
				return Players::Action::Move;
			case Functions::Keys::Key::N4:
				return Players::Action::Orient;
			case Functions::Keys::Key::N5:
				return Players::Action::Nothing;
			case Functions::Keys::Key::N0:
				throw exceptions::exit_game(); //you can always exit and go back to menu
			default:
				break;
		}
	};
}

void CLI::victory( Siam::Player& player ) { //victory
	cli.clearScreen();

	this->m_fmod.stopMusic(); //stops music
	std::ifstream logo( "texts/victory.txt" );

	if( logo ) {
		std::string ligne;

		while( getline( logo, ligne ) ) {
			std::cout << ligne << std::endl;
		}
	} else {
		throw std::ios_base::failure( "File not found: texts/victory.txt" );
	}

	this->m_fmod.playSoundWait( "victory" ); //plays victory sound
	this->m_fmod.playMusic( "victory" ); //plays victory music

	std::cout << std::endl << std::endl << "Bravo " << player.getName() << ", tu as gagne!" << std::endl; //displays the winning player
    SLEEP( 4000 );
    std::cout << "Press any key to continue..." << std::endl ;
	while( kbhit() ) //waits for the use to hit keyboard
		getch();

	getch();
}

void CLI::loadDisplayMatrix() { //loads the matrix in the program
	std::string tmp;
	std::ostringstream tmp2;

    //some complicated stuff, we're just charging up the matrix in memory
	tmp = " ";
	for( unsigned int i = 0; i < this->m_board.size() - 1; i++ )
		tmp += "_____";
	tmp += "____       ";
	this->m_displayMatrix.push_back( tmp );

	tmp = "";
	for( unsigned int i = 0; i < this->m_board.size(); i++ ) {
		tmp += "| ";
		tmp += ( char ) ( 'A' + i );
		tmp += "  ";
	}
	tmp += "|";
	this->m_displayMatrix.push_back( tmp );

	tmp = "";
	for( unsigned int i = 0; i < this->m_board.size(); i++ ) {
		tmp += "|____";
	}
	tmp += "|";
	this->m_displayMatrix.push_back( tmp );

	tmp = " ";
	for( unsigned int i = 0; i < this->m_board.size() - 1; i++ ) {
		tmp += "_____";
	}
	tmp += "____   ____";
	this->m_displayMatrix.push_back( tmp );

	for( unsigned int j = 0; j < this->m_board.size() * 2; j++ ) {
		tmp2.str( "" );
		for( unsigned int i = 0; i < this->m_board[ j / 2 ].size(); i++ ) {
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


