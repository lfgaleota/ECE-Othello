/// \author { Louis-Félix Galeota, Romain Brisse }
/// \date 24 Avril 2017

#include "othello/inc/ui/main/mainallegroui.hpp"
#include "othello/inc/ui/main/maincliui.hpp"
#include "othello/inc/ui/audio/FMOD.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;



int main( int argc, char* argv[] ) {
	Othello::UI::Audio::FMOD fmod;

	fmod.loadMusic( "menu", "musics/menu.it" );
	fmod.loadMusic( "main1", "musics/main1.it" );
	fmod.loadMusic( "victory", "musics/victorybg.it" );
	fmod.loadSound( "victory", "musics/victory.it" );
	fmod.loadSound( "back", "sounds/back.wav" );
	fmod.loadSound( "clickNextCard", "sounds/clickNextCard.wav" );
	fmod.loadSound( "hoverButton", "sounds/hoverButton.wav" );
	fmod.loadSound( "hoverCard", "sounds/hoverCard.wav" );
	fmod.setMasterVolume( 1.0f );

	if( argc > 1 ) {
		std::string arg1 = argv[ 1 ];

		if( arg1 == "--cli" ) {
			Othello::UI::Main::CLI cliui( fmod );
			return 0;
		}
	}

	try {
		Othello::UI::Main::Allegro allegroui( fmod );
	} catch( runtime_error& e ) {
		stringstream error;
		error << "Une erreur est survenu durant l'exécution du programme." << endl << endl
		      << "Runtime error: "
		      << typeid( e ).name() << endl
		      << e.what();
		allegro_message( error.str().c_str() );
	} catch( exception& e ) {
		stringstream error;
		error << "Une erreur est survenu durant l'exécution du programme." << endl << endl
		      << "Exception: "
		      << typeid( e ).name() << endl
		      << e.what();
		allegro_message( error.str().c_str() );
	} catch( ... ) {
		stringstream error;
		error << "Une erreur est survenu durant l'exécution du programme.";
		allegro_message( error.str().c_str() );
	}

	return 0;
}

END_OF_MAIN();