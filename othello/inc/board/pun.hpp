#ifndef _ECE_OTHELLO_BOARD_PUN_HPP_
#define _ECE_OTHELLO_BOARD_PUN_HPP_

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
			 * @struct PunCount
			 * @brief Gère le nombre de pions du plateau
			 */
			struct PunCount {
				unsigned char white = 0;
				unsigned char black = 0;
			};

			/**
			 * @struct Pun
			 * @brief Structure regroupant les couleurs des pions et fonctions associées
			 */
			struct Pun {
				/**
				 * @enum Colors
				 * @brief Représente les couleurs possible d'un pion
				 */
				enum Colors {
					blank = 0, /*! < Pas de pion */
					black = 1, /*! < Pion noir */
					white = 2 /*! < Pion blanc */
				};

				/**
				 * @brief Donne la couleur opposée
				 * @param color Couleur
				 * @return Couleur opposée
				 */
				static inline Colors opposite( Colors color ) {
					return ( Colors ) ( ( int ) white - ( int ) color + ( int ) black );
				}

				/**
				 * @brief Vérificateur de validiété d'entier
				 * @details Vérifie si un entier peut être casté sans problèmes vers une couleur #Colors
				 * @param v Entier
				 * @return Possibilité de caster
				 */
				static bool check( int v );
			};
		}
	}

#endif
