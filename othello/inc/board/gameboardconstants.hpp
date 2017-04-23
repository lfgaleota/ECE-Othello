#ifndef _ECE_OTHELLO_BOARD_GAMEBOARDCONSTANTS_HPP_
	#define _ECE_OTHELLO_BOARD_GAMEBOARDCONSTANTS_HPP_

	#include "pun.hpp"

	/**
	* @namespace Othello
	* @details Espace de nommage du jeu.
	*/
	namespace Othello {
		/**
		 * @namespace Board
		 * @details Espace de nommage regroupant les éléments liés au plateau de jeu
		 */
		namespace Board {
			const static unsigned char sizeEdge = 8; /*! < Taille d'une arrête du plateau */
			const static unsigned char size = sizeEdge * sizeEdge; /*! < Taille totale du plateau */
			const static size_t sizeMemory = (size_t) ( size * 4 ); /*! < Emprise mémoire du plateau */

			typedef Pun::Colors (*punArray)[ sizeEdge ]; /*! < Type pointeur vers plateau */
		}
	}
#endif
