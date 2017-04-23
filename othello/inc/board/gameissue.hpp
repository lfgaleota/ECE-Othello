#ifndef _ECE_OTHELLO_BOARD_GAMEISSUE_HPP_
	#define _ECE_OTHELLO_BOARD_GAMEISSUE_HPP_

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
			/**
			 * @enum GameIssue
			 * @brief Représente l'issue d'une partie
			 */
			enum GameIssue {
				Nothing, /*! < Rien de spécial (la partie continue) */
				Victory, /*! < Victoire */
				Defeat, /*! < Défaite */
				Draw /*! < Match nul */
			};
		}
	}

#endif
