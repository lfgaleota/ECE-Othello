#ifndef _FUNCTIONS_CLI_HPP_
	#define _FUNCTIONS_CLI_HPP_

	#include <iostream>
	#include <cstdio>

	#ifdef ANSI_TERM

		#include <unistd.h>

	#elif _WIN32 || __WIN32 || __WIN32__

		#define WIN

		#include "../winhack.h"
		#include <conio.h>

		#define SLEEP(ms) Sleep(ms)

	#elif __APPLE__ || __linux || __linux__ || __unix || __unix__ || __posix

		#define UNIX

		#include <sys/ioctl.h>
		#include <unistd.h>
		#include <term.h>
		#include <termios.h>

		#define SLEEP(ms) usleep(ms*1000)

		int getch();
		char kbhit();

	#endif

	#if defined( ANSI_TERM ) || defined( UNIX )
		#define FOREGROUND_BLUE 0x01
		#define FOREGROUND_RED 0x02
		#define FOREGROUND_GREEN 0x04
		#define FOREGROUND_INTENSITY 0x08
		#define BACKGROUND_BLUE 0x10
		#define BACKGROUND_RED 0x20
		#define BACKGROUND_GREEN 0x40
		#define BACKGROUND_INTENSITY 0x80
	#endif

	namespace Functions {
		namespace Keys {
			enum Key {
				ArrowLeft,
				ArrowRight,
				ArrowUp,
				ArrowDown,
				Enter,
				Escape,
				N0,
				N1,
				N2,
				N3,
				N4,
				N5,
				N6,
				N7,
				N8,
				N9,
				Invalid
			};
		}

		class CLI {
			private:
				#if defined( WIN )
				CONSOLE_SCREEN_BUFFER_INFO attributes;
				#elif defined( UNIX )
				static struct termios initTermios( bool echo );
				static int getch();
				static void resetTermios( struct termios oldIO );
				#endif

			public:
				/****
					Constructeur de la classe.
				****/
				CLI();

				/****
					Destructeur de la classe, permet de remettre à zéro la mise en forme de la console et effacer l'écran pour quitter proprement.
				****/
				~CLI();

				/****
					Permet d'effacer la sortie de la console. Dépend du système.
					Demande:
						- Rien
					Retourne:
						- Rien
				****/
				static void clearScreen();

				/****
					Permet de changer la couleur d'avant-plan et d'arrière-plan de la console. Dépend du système.
					Demande:
						- Ensemble de couleur
					Retourne:
						- Rien
				****/
				void setColor( unsigned char color );

				/****
					Permet de réinitialiser la mise en forme de la console. Dépend du système.
					Demande:
						- Rien
					Retourne:
						- Rien
				****/
				void resetColor();

				/****
					Permet de déplacer le curseur à des coordonnées précise. Dépend du système.
					Demande:
						- Colonne
						- Ligne
					Retourne:
						- Rien
				****/
				static void moveCursor( unsigned int line, unsigned int column );

				/****
					Permet de récupérer la taille de la console. Dépend du système.
					Demande:
						- Rien
					Retourne:
						- Largeur de la console (par référence)
						- Hauteur de la console (par référence)
				****/
				void getSize( unsigned int& width, unsigned int& height );

				/****
					Permet de récupérer les coordonnées permettant de centrer un élément de taille donnée dans la console. Dépend du système.
					Demande:
						- Largeur de l'élément
						- Hauteur de l'élément
					Retourne:
						- Colonne où placer l'élément (par référence)
						- Ligne où palcer l'élément (par référence)
				****/
				static void
				setOffsets( unsigned int width, unsigned int height, unsigned int& offset_x, unsigned int& offset_y );

				/****
					Permet d'effectuer une pause silencieuse dans la console.
					Demande:
						- Rien
					Retourne:
						- Rien
				****/
				static void pause();

				static Keys::Key getKey();
		};
	}
#endif
