#ifndef _ECE_OTHELLO_SAVE_SAVE_HPP_
	#define _ECE_OTHELLO_SAVE_SAVE_HPP_

	#include <iostream>
	#include <fstream>
	#include <string>
	#include <vector>
	#include "../board/gameboardconstants.hpp"
	#include "../board/pun.hpp"

	/**
	 * @namespace Othello
	 * @details Espace de nommage du jeu.
	 */
	namespace Othello {
		namespace Players {
			class Player;
		}

		/**
		 * @namespace Save
		 * @details Espace de nommage regroupant les entitées liées à la sauvegarde.
		 */
		namespace Save {

			/**
			 * @struct Save
			 * @brief Structure comportant toutes les informations pour reprendre une partie
			 */
			struct Save {
				Othello::Board::Pun::Colors board[Othello::Board::sizeEdge][Othello::Board::sizeEdge]; /*! < Plateau */
				uint64_t emptyNeighbors; /*! < Voisins vides */
				Othello::Board::PunCount count; /*! < Nombre de pions */
				std::vector<Othello::Players::Player*> players; /*! < Joueurs */
				unsigned char currentPlayer; /*! < Index du joueur actuel */
			};
		}
	}

#endif
