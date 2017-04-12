#include "cli.hpp"

using namespace Functions;

/****
	Permet d'effectuer une pause silencieuse dans la console.
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::pause() {
	std::cin.ignore( std::cin.rdbuf()->in_avail() );
	std::getchar();
}

#if defined( ANSI_TERM )

/****
	Constructeur de la classe.
****/
CLI::CLI() {}

/****
	Permet d'effacer la sortie de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::clearScreen()  {
	// Codes ANSI pour efface la sortie du terminal
	const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";

	// Ces codes ANSI, pour une raison quelconque, font que tout texte suivant directement a son 1er caractère recopié avec un espace avant, ceci avant son affichage.
	write( STDOUT_FILENO, CLEAR_SCREE_ANSI, 12 );

	// Ce write évite le problème, mais affiche une ligne vide.
	write( STDOUT_FILENO, " \n", 0);

	// REMARQUE: On retrouve le même comportement avec les commandes natives cls ou clear. Il est possible que ces commandes utilisent les mêmes codes ANSI.
}

#elif defined( WIN )

/****
	Constructeur de la classe.
****/
CLI::CLI() {
	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	// Récupération des attributs actuels de la console
	GetConsoleScreenBufferInfo( hConsole, &this->attributes );
}

/****
	Destructeur de la classe, permet de remettre à zéro la mise en forme de la console et effacer l'écran pour quitter proprement.
****/
CLI::~CLI() {
	this->resetColor();
	this->clearScreen();
}

/****
	Permet d'effacer la sortie de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::clearScreen() {
	HANDLE						hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	DWORD						count;
	DWORD						cellCount;
	COORD						homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if( hStdOut == INVALID_HANDLE_VALUE ) return;

	// Obtenir la taille du buffer
	if( !GetConsoleScreenBufferInfo( hStdOut, &csbi  )) return;
	cellCount = (DWORD) ( csbi.dwSize.X * csbi.dwSize.Y );

	// Remplir le buffer avec des espaces
	if( !FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		) ) return;

	// Remplir le buffer les attributs et couleurs actuelles
	if( !FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		) ) return;

	// Déplacer le curseur à sa position initiale
	SetConsoleCursorPosition( hStdOut, homeCoords );
}

#elif defined( UNIX )

/****
	Constructeur de la classe.
****/
CLI::CLI() {}

/****
	Destructeur de la classe, permet de remettre à zéro la mise en forme de la console et effacer l'écran pour quitter proprement.
****/
CLI::~CLI() {
	this->resetColor();
	this->clearScreen();
}

/****
	Permet d'effacer la sortie de la console. Dépend du système
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::clearScreen() {
	if( !cur_term ) {

		int result;
		setupterm( NULL, STDOUT_FILENO, & result );
		if( result <= 0 ) return;

	}

	putp( tigetstr( "clear" ) );
}

/****
	Permet de récupérer la taille de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Largeur de la console (par référence)
		- Hauteur de la console (par référence)
****/
void CLI::getSize( unsigned int& width, unsigned int& height ) {
	// On récupère la taille
	struct winsize w;
	ioctl( STDOUT_FILENO, TIOCGWINSZ, & w );

	width = w.ws_col;
	height = w.ws_row;
}

/****
	Permet de récupérer les coordonnées permettant de centrer un élément de taille donnée dans la console. Dépend du système.
	Demande:
		- Largeur de l'élément
		- Hauteur de l'élément
	Retourne:
		- Colonne où placer l'élément (par référence)
		- Ligne où palcer l'élément (par référence)
****/
void CLI::setOffsets( unsigned int width, unsigned int height, unsigned int& u_offset_x, unsigned int& u_offset_y ) {
	int offset_x, offset_y;

	// On récupère la taille
	struct winsize w;
	ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );

	// On calcule les offsets de manière à centrer l'élément, sans déborder sur les côtés
	offset_y = ( ( w.ws_row - 1 ) - height ) / 2;
	offset_x = ( ( w.ws_col - 1 ) - width ) / 2;

	u_offset_x = ( offset_x >= 0 ? (unsigned) offset_x : 0 );
	u_offset_y = ( offset_y >= 0 ? (unsigned) offset_y : 0 );
}

struct termios CLI::initTermios( bool echo ) {
	struct termios oldIO;
	tcgetattr( 0, &oldIO );
	struct termios newIO = oldIO;
	newIO.c_lflag &= ~ICANON;
	newIO.c_lflag &= ( echo ? ECHO : ~ECHO );
	tcsetattr( 0, TCSANOW, &newIO );
	return oldIO;
}

void CLI::resetTermios( struct termios oldIO ) {
	tcsetattr( 0, TCSANOW, &oldIO );
}

int CLI::getch() {
	int ch;
	struct termios oldIO = initTermios( false );
	ch = getchar();
	resetTermios( oldIO );
	return ch;
}

Keys::Key CLI::getKey() {
	// Initialisation de la variable et récupération de la touche appuyée
	unsigned int key = getch();

	/**
		getch() retourne 2 valeurs dans le buffer pour les touches fléchées:
			- 0xffffffe0 (code touche Esc)
			- 0x48, 0x50, 0x4D ou 0x4B (respectivement fléche haut, bas, droit et gauche)
		getch() retourne simplement 0x1B pour la touche Esc
		getch() retourne simplement 0x0D pour la touche Entrée

		On cherche alors à vérifier dans quel cas on est:
		- si on a le code pour la touche ESC, alors on a soit appuyé sur ESC, soit sur une touche fléchée
			-> si on a le code pour '[', alors on a appuyé sur une touche fléchée
			-> sinon, on a appuyé sur la touche ESC
		- si on a le code '\r', alors on a appuyé sur la touche Entrée
	**/

	switch( key ) {
		case 0x0A:
			// Si le code correpond à la touche Entrée
			return Keys::Key::Enter;

		case 0x31:
		case 0x26:
			// Si le code correspond à la touche 1
			return Keys::Key::N1;

		case 0x32:
			// Si le code correspond à la touche 2
			return Keys::Key::N2;

		case 0x33:
		case 0x22:
			// Si le code correspond à la touche 3
			return Keys::Key::N3;

		case 0x34:
		case 0x27:
			// Si le code correspond à la touche 4
			return Keys::Key::N4;

		case 0x35:
		case 0x28:
			// Si le code correspond à la touche 5
			return Keys::Key::N5;

		case 0x36:
		case 0x2D:
			// Si le code correspond à la touche 6
			return Keys::Key::N6;

		case 0x37:
			// Si le code correspond à la touche 7
			return Keys::Key::N7;

		case 0x38:
		case 0x5F:
			// Si le code correspond à la touche 8
			return Keys::Key::N8;

		case 0x39:
			// Si le code correspond à la touche 9
			return Keys::Key::N9;

		case 0x30:
			// Si le code correspond à la touche 0
			return Keys::Key::N0;

		case 0xC3:
			// Les touches "en dessous de" 2, 7, 9, 0 reportent un code en deux valeurs dont la 1ère partie est 0xC3
			key = getch();

			switch( key ) {
				// Récupérer la 2nde valeure

				case 0xA9:
					// Si le code correspond à la touche 2
					return Keys::Key::N2;
				case 0xA8:
					// Si le code correspond à la touche 7
					return Keys::Key::N7;
				case 0xA7:
					// Si le code correspond à la touche 9
					return Keys::Key::N9;
				case 0xA0:
					// Si le code correspond à la touche 0
					return Keys::Key::N0;

				default:
					// Aucune, donc on est en présence d'une "valeur invalide" (non traitée ici)
					return Keys::Key::Invalid;
			}

		case 0x1B:
			// Si le code correspond à la 1ère valeur des touches fléchées et touche Echap
			key = getch();

			switch( key ) {
				// Récupérer la 2nde valeure

				case 0x5B:
					// Si on obtient le 2nd code des touches fléchées, on récupère la 3ème valeure
					key = getch();

					switch( key ) {
						// Récupérer la 3ème valeure

						case 0x41:
							// Flèche haut
							return Keys::Key::ArrowUp;

						case 0x42:
							// Flèche bas
							return Keys::Key::ArrowDown;

						case 0x44:
							// Flèche gauche
							return Keys::Key::ArrowLeft;

						case 0x43:
							// Flèche droite
							return Keys::Key::ArrowRight;

						default:
							// Aucune des flèches, donc on est en présence d'une "valeur invalide" (non traitée ici)
							return Keys::Key::Invalid;
					}

				default:
					// Aucune des flèches, donc on est en présence d'une "valeur invalide" (non traitée ici)
					return Keys::Key::Invalid;
			}

		default:
			// Aucune condition n'a été vérifiée, donc on est en présence d'une "valeur invalide" (non traitée ici)
			return Keys::Key::Invalid;
	}
}

#endif

#if defined( UNIX ) || defined( ANSI_TERM )

/****
	Permet de déplacer le curseur à des coordonnées précise. Dépend du système.
	Demande:
		- Colonne
		- Ligne
	Retourne:
		- Rien
****/
void CLI::moveCursor( unsigned int line, unsigned int column ) {
	std::cout << "\033[" << line + 1 << ";" << column + 1 << "H";
}

/****
	Permet de changer la couleur d'avant-plan et d'arrière-plan de la console. Dépend du système.
	Demande:
		- Ensemble de couleur --> exemple : setColor(FOREGROUND_RED | BACKGROUND_BLUE); + si on ne met pas de background, il est noir par défaut !
	Retourne:
		- Rien
****/
void CLI::setColor( unsigned char color ) {
	std::string colorCodes;

	if( color & ( BACKGROUND_INTENSITY | FOREGROUND_INTENSITY ) ) {
		colorCodes += "\33[1m"; // Intensity
	}

	if( color & FOREGROUND_RED && color & FOREGROUND_GREEN && color & FOREGROUND_BLUE ) {
		colorCodes += "\33[37m"; // White
	} else if( color & FOREGROUND_RED && color & FOREGROUND_GREEN ) {
		colorCodes += "\33[33m"; // Yellow
	} else if( color & FOREGROUND_RED && color & FOREGROUND_BLUE ) {
		colorCodes += "\33[35m"; // Magenta
	} else if( color & FOREGROUND_GREEN && color & FOREGROUND_BLUE ) {
		colorCodes += "\33[36m"; // Cyan
	} else if( color & FOREGROUND_RED ) {
		colorCodes += "\33[31m"; // Red
	} else if( color & FOREGROUND_GREEN ) {
		colorCodes += "\33[32m"; // Green
	} else if( color & FOREGROUND_BLUE ) {
		colorCodes += "\33[34m"; // Blue
	} else {
		colorCodes += "\33[30m"; // Black
	}

	if( color & BACKGROUND_RED && color & BACKGROUND_GREEN && color & BACKGROUND_BLUE ) {
		colorCodes += "\33[47m"; // White
	} else if( color & BACKGROUND_RED && color & BACKGROUND_GREEN ) {
		colorCodes += "\33[43m"; // Yellow
	} else if( color & BACKGROUND_RED && color & BACKGROUND_BLUE ) {
		colorCodes += "\33[45m"; // Magenta
	} else if( color & BACKGROUND_GREEN && color & BACKGROUND_BLUE ) {
		colorCodes += "\33[46m"; // Cyan
	} else if( color & BACKGROUND_RED ) {
		colorCodes += "\33[41m"; // Red
	} else if( color & BACKGROUND_GREEN ) {
		colorCodes += "\33[42m"; // Green
	} else if( color & BACKGROUND_BLUE ) {
		colorCodes += "\33[44m"; // Blue
	} else {
		colorCodes += "\33[40m"; // Black
	}

	std::cout << colorCodes;
}

/****
	Permet de réinitialiser la mise en forme de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::resetColor() {
	std::cout << "\033[0m";
}

#elif defined( WIN )

/****
	Permet de déplacer le curseur à des coordonnées précise. Dépend du système.
	Demande:
		- Colonne
		- Ligne
	Retourne:
		- Rien
****/
void CLI::moveCursor( unsigned int line, unsigned int column ) {
	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	if( hConsole == INVALID_HANDLE_VALUE ) return;

	// Définition d'une structure coordonéees
	COORD destCoords;
	destCoords.X = column;
	destCoords.Y = line;

	// Définition de la nouvelle position du curseur
	SetConsoleCursorPosition( hConsole, destCoords );
}

/****
	Permet de changer la couleur d'avant-plan et d'arrière-plan de la console. Dépend du système.
	Demande:
		- Ensemble de couleur
	Retourne:
		- Rien
****/
void CLI::setColor( unsigned char color ) {
	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	// Application des nouveaux attributs de couleur
	SetConsoleTextAttribute( hConsole, (WORD) color );
}

/****
	Permet de réinitialiser la mise en forme de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::resetColor() {
	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	// Restauration des attributs initiaux
	SetConsoleTextAttribute( hConsole, this->attributes.wAttributes );
}

/****
	Permet de récupérer la taille de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Largeur de la console (par référence)
		- Hauteur de la console (par référence)
****/
void CLI::getSize( unsigned int& width, unsigned int& height ) {
	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	// Définition des variables utiles
	CONSOLE_SCREEN_BUFFER_INFO consoleInfos;

	// Récupération des attributs actuels de la console
	GetConsoleScreenBufferInfo( hConsole, &consoleInfos );

	/*
	 * consoleInfos.srWindow.Right - consoleInfos.srWindow.Left donne le nombre de colonnes en partant de 0
	 * consoleInfos.srWindow.Bottom - consoleInfos.srWindow.Top  donne le nombre de lignes en partant de 0
	 */
	width = consoleInfos.srWindow.Right - consoleInfos.srWindow.Left + 1;
	height = consoleInfos.srWindow.Bottom - consoleInfos.srWindow.Top + 1;
}

/****
	Permet de récupérer les coordonnées permettant de centrer un élément de taille donnée dans la console. Dépend du système.
	Demande:
		- Largeur de l'élément
		- Hauteur de l'élément
	Retourne:
		- Colonne où placer l'élément (par référence)
		- Ligne où palcer l'élément (par référence)
****/
void CLI::setOffsets( unsigned int width, unsigned int height, unsigned int& u_offset_x, unsigned int& u_offset_y ) {
	int offset_x, offset_y;

	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	// Définition des variables utiles
	CONSOLE_SCREEN_BUFFER_INFO consoleInfos;

	// Récupération des attributs actuels de la console
	GetConsoleScreenBufferInfo( hConsole, &consoleInfos );

	/*
	 * consoleInfos.srWindow.Right - consoleInfos.srWindow.Left donne le nombre de colonnes en partant de 0
	 * consoleInfos.srWindow.Bottom - consoleInfos.srWindow.Top  donne le nombre de lignes en partant de 0
	 */

	// On calcule les offsets de manière à centrer l'élément, sans déborder sur les côtés
	offset_x = ( ( consoleInfos.srWindow.Right - consoleInfos.srWindow.Left + 1 ) -  width ) / 2;
	offset_y = ( ( consoleInfos.srWindow.Bottom - consoleInfos.srWindow.Top + 1 ) - height ) / 2 ;

	u_offset_x = ( offset_x >= 0 ? (unsigned) offset_x : 0 );
	u_offset_y = ( offset_y >= 0 ? (unsigned) offset_y : 0 );
}

/****
	Permet de récupérer l'appuie sur une touche du clavier
    Demande:
        - Rien
	Retourne:
		- 0 pour UNE VALEUR INVALIDE
		- 1 pour la flèche du haut
		- 2 pour la flèche du bas
		- 3 pour la flèche de gauche
		- 4 pour la flèche de droite
		- 5 pour la touche Entrée
		- 6 pour la touche ESC
		- '1' pour la touche 1
		- '2' pour la touche 2
		...
		- '0' pour la touche 0
****/

Keys::Key CLI::getKey() {
		// Initialisation de la variable et récupération de la touche appuyée
	unsigned int key = getch();

	/**
		getch() retourne 2 valeurs dans le buffer pour les touches fléchées:
			- 0xffffffe0 (code touche Esc)
			- 0x48, 0x50, 0x4D ou 0x4B (respectivement fléche haut, bas, droit et gauche)
		getch() retourne simplement 0x1B pour la touche Esc
		getch() retourne simplement 0x0D pour la touche Entrée

		On cherche alors à vérifier dans quel cas on est:
		- si on a le code pour la touche ESC, alors on a soit appuyé sur ESC, soit sur une touche fléchée
			-> si on a le code pour '[', alors on a appuyé sur une touche fléchée
			-> sinon, on a appuyé sur la touche ESC
		- si on a le code '\r', alors on a appuyé sur la touche Entrée
	**/
	switch( key ) {
		case 0x0D:
			// Si le code correpond à la touche Entrée
			return Keys::Key::Enter;

		case 0x1B:
			// Si le code correspond à la touche Esc, on retourne Esc
			return Keys::Key::Escape;

		case '1':
		case 38:
			// Si le code correspond à la touche 1
			return Keys::Key::N1;

		case '2':
		case 130:
			// Si le code correspond à la touche 2
			return Keys::Key::N2;

		case '3':
		case 34:
			// Si le code correspond à la touche 3
			return Keys::Key::N3;

		case '4':
		case 39:
			// Si le code correspond à la touche 4
			return Keys::Key::N4;

		case '5':
		case 40:
			// Si le code correspond à la touche 5
			return Keys::Key::N5;

		case '6':
		case 45:
			// Si le code correspond à la touche 6
			return Keys::Key::N6;

		case '7':
		case 138:
			// Si le code correspond à la touche 7
			return Keys::Key::N7;

		case '8':
		case 95:
			// Si le code correspond à la touche 8
			return Keys::Key::N8;

		case '9':
		case 135:
			// Si le code correspond à la touche 9
			return Keys::Key::N9;

		case '0':
		case 133:
			// Si le code correspond à la touche 0
			return Keys::Key::N0;

		case 0xE0:
			// Si le code correspond à la 1ère valeur des touches fléchées
			switch( getch() ) {
				// Récupérer la 2nde valeure

				case 0x48:
					// Flèche haut
					return Keys::Key::ArrowUp;

				case 0x50:
					// Flèche bas
					return Keys::Key::ArrowDown;

				case 0x4B:
					// Flèche gauche
					return Keys::Key::ArrowLeft;

				case 0x4D:
					// Flèche droite
					return Keys::Key::ArrowRight;

				default:
					// Aucune des flèches, donc on est en présence d'une "valeur invalide" (non traitée ici)
					return Keys::Key::Invalid;
			}

		default:
			// Aucune condition n'a été vérifiée, donc on est en présence d'une "valeur invalide" (non traitée ici)
			return Keys::Key::Invalid;
	}
}

#endif
