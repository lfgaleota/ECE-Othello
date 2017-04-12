#include "menu.hpp"

using namespace std;
using namespace Functions;

void CLIs::Menu::setOffsets( unsigned int& offset_x, unsigned int& offset_y ) {
	//Useful variables
	unsigned int len, width = this->m_header.size();

	//Browse ton get back, max width
	for( const auto& choice : this->m_choices ) {
		len = choice.size();

		// If we go across that width
		if( width < len ) {
			//save it
			width = len;
		}
	}

	// Then get the offsets in order to center the game
	CLI::setOffsets( width, this->m_choices.size() + 1, offset_x, offset_y );
}

/****
	Permet d'afficher un menu interactif, utilisant les touches flechees, Entree et Esc
	 Demande:
		 - Le texte a afficher en haut du menu
		 - Les choix
	Retourne:
		- Entier >= 1 representant le choix
		- 0 si aucun choix n'a ete fait
****/
CLIs::Menu::Menu( string header, vector<string> choices, unsigned char back_color, unsigned char header_color, unsigned char selection_color, unsigned int minimal_height, void ( *intermediateDisplay )() ) : m_header( header ), m_choices( choices ) {
	//Useful variables
	unsigned int exit = 0, offset_x = 0, offset_y = 0;
	Keys::Key key;
	CLI cli = CLI();

	//get the offsets to center menu
	setOffsets( offset_x, offset_y );
	if( minimal_height > offset_y )
		offset_y = minimal_height;

	while( exit == 0 ) {
		//Get the background color
		cli.setColor( back_color );

		//Erase previous displays
		cli.clearScreen();

		// On appelle la fonction d'affichage intermédiaire
		if( intermediateDisplay != nullptr )
			intermediateDisplay();

		//Set foreground color
		cli.setColor( header_color );
		//Positioning (taking the offsets into account)
		cli.moveCursor( offset_y, offset_x );

		// Display
		if( header.size() > 0 )
			cout << "=== " << header << " ===" << endl;

		for( unsigned int i = 0; i < this->m_choices.size() ; i++ ) {
			// Display the choices
			if( this->m_choice == i + 1) {
				// If it matches the text put the appropriate color
				cli.setColor( selection_color );
			} else {
				//else display background
				cli.setColor( back_color );
			}

			// move the the supposed location
			cli.moveCursor( offset_y + i + 1, offset_x );

			//display text
			cout << this->m_choices[ i ] << endl;
		}

		//get the pressed key --> something like kbhit
		key = cli.getKey();

		switch( key ) {
			case Keys::Key::ArrowUp:
				// Last choice
				if( this->m_choice > 1 )
					this->m_choice--;
				break;
			case Keys::Key::ArrowDown:
				//Next choice
				if( this->m_choice < this->m_choices.size() )
					this->m_choice++;
				break;
			case Keys::Key::Escape:
				// choice equals zero if you press escape
				// means we'll get out of the loop
				this->m_choice = 0;
			case Keys::Key::Enter:
				//If you press enter or escape you leave the menu ! --> recursivity condition
				exit = 1;
				break;
			default:
				break;
		}

	}

	//Reset colors to normal
	cli.resetColor();

	//erase previous displays
	cli.clearScreen();
}

unsigned int CLIs::Menu::getChoice() const { //read access to the choice made by user for the menu
	return this->m_choice;
}
