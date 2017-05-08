#include "../../inc/ui/main/maincliui.hpp"

using namespace Othello;
using namespace Othello::UI::Main;

CLI::CLI( Othello::UI::Audio::FMOD& fmod ) : m_fmod( fmod ) {
	#ifdef WIN
	SetConsoleTitle( "ECE Othello" );
	HWND hWnd = GetConsoleWindow();
	HICON hicon = (HICON) LoadIcon( GetModuleHandle( NULL ), MAKEINTRESOURCE( PROGICON ) );
	SendMessage( hWnd, WM_SETICON, ICON_SMALL, (LPARAM) hicon );
	#endif
	menu();
}

void CLI::logo() {
	std::ifstream logoFile( "texts/logo.txt" );

	if( logoFile.is_open() ) {
		std::string ligne;
		unsigned int x = 0, y = 0;
		Functions::CLI::setOffsets( LOGO_WIDTH, 0, x, y );

		for( unsigned int i = 0; getline( logoFile, ligne ); i++ ) {
			Functions::CLI::moveCursor( i, x );
			std::cout << ligne;
		}
	} else {
		throw std::ios_base::failure( "File not found: texts/siam.txt" );
	}
}

void CLI::menu() {
	std::vector<std::string> choices = {
		"Continuer",
		"Nouvelle partie",
	    "Quitter"
	};
	m_cli.clearScreen();
	Functions::CLIs::Menu* menu;

	for( bool loop = true; loop; ) {
		menu = new Functions::CLIs::Menu( "", choices, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY, 0, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY, LOGO_HEIGHT + 1, CLI::logo );

		switch( menu->getChoice() ) {
			case 1:
				loadGame();
				break;

			case 2:
				newGame();
				break;

			case 3:
				loop = false;
				break;

			default:
				break;
		}

		delete menu;
	}
}

void CLI::loadGame() {
	if( Othello::Save::SaveManager::check() ) {
		try {
			Othello::Game game2( m_fmod, false );
		} catch( std::logic_error e ) {
			std::cout << e.what() << std::endl;
			getchar();
		}
	} else {
		std::cout << "Pas de sauvegarde !" << std::endl;
		getchar();
	}
}

void CLI::newGame() {
	std::vector<std::string> choices = {
		"Joueur VS Joueur",
		"Joueur VS IA",
	    "< Retour"
	};
	m_cli.clearScreen();
	Functions::CLIs::Menu* menu;

	for( bool loop = true; loop; ) {
		menu = new Functions::CLIs::Menu( "Nouvelle partie", choices, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,  BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY );

		switch( menu->getChoice() ) {
			case 1:
				newPVP();
				loop = false;
				break;

			case 2:
				newPVAI();
				loop = false;
				break;

			case 3:
				loop = false;
				break;

			default:
				break;
		}

		delete menu;
	}
}

void CLI::newPVP() {
	m_players.clear();
	std::string nameOfPlayer;

	m_cli.moveCursor(10,70);
	std::cout << "Entrez le nom du joueur 1 : " ;
	m_cli.moveCursor(12,70);
	std::cin >> nameOfPlayer;
	m_players.push_back( new Othello::Players::Human( nameOfPlayer, Othello::Board::Pun::Colors::black ) );

	m_cli.moveCursor(15,70);
	std::cout << "Entrez le nom du joueur 2 : " ;
	m_cli.moveCursor(17,70);
	std::cin >> nameOfPlayer;
	m_players.push_back( new Othello::Players::Human( nameOfPlayer, Othello::Board::Pun::Colors::white ) );

	try {
		Othello::Game game1( m_players, m_fmod, false );
	} catch( std::logic_error e ) {
		std::cout << e.what() << std::endl;
		getchar();
	}

	for( Othello::Players::Player* player : m_players ) {
		delete player;
	}
}

void CLI::newPVAI() {
	std::vector<std::string> choices = {
		"Debutant",
		"Facile",
		"Normale",
	    "< Retour"
	};
	m_cli.clearScreen();
	Functions::CLIs::Menu* menu;

	m_players.clear();

	for( bool loop = true; loop; ) {
		menu = new Functions::CLIs::Menu( "Niveau de difficulté", choices, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,  BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY );

		switch( menu->getChoice() ) {
			case 1:
				m_players.push_back( new Othello::Players::RandomAI( "IA", Othello::Board::Pun::Colors::white ) );
				loop = false;
				break;

			case 2:
				m_players.push_back( new Othello::Players::SimpleAI( "IA", Othello::Board::Pun::Colors::white ) );
				loop = false;
				break;

			case 3:
				m_players.push_back( new Othello::Players::EnhancedAI( "IA", Othello::Board::Pun::Colors::white ) );
				loop = false;
				break;

			case 4:
				return;

			default:
				break;
		}

		delete menu;
	}

	std::string nameOfPlayer;

	m_cli.moveCursor(10,70);
	std::cout << "Entrez votre nom : " ;
	m_cli.moveCursor(12,70);
	std::cin >> nameOfPlayer;
	m_players.push_back( new Othello::Players::Human( nameOfPlayer, Othello::Board::Pun::Colors::black ) );

	try {
		Othello::Game game1( m_players, m_fmod, false );
	} catch( std::logic_error e ) {
		std::cout << e.what() << std::endl;
		getchar();
	}

	for( Othello::Players::Player* player : m_players ) {
		delete player;
	}
}