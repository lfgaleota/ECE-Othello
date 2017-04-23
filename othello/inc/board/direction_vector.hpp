#ifndef _ECE_OTHELLO_BOARD_DIRECTIONVECTOR_HPP_
	#define _ECE_OTHELLO_BOARD_DIRECTIONVECTOR_HPP_

	#include <list>

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
			 * @struct DirectionVector
			 * @brief Structure représentant un vecteur de direction
			 * @details Le vecteur de direction indique un déplacement dans un espace en deux dimensions.
			 */
			struct DirectionVector {
				const char x; /*! < Coordonnée en abscisse */
				const char y; /*! < Coordonnée en ordonnée */

				/**
				 * @brief Constructeur
				 * @param direction_x Coordonnée en abscisse
				 * @param direction_y Coordonnée en ordonnée
				 */
				DirectionVector( char direction_x, char direction_y );
			};
		}
	}

	/**
	 * @brief Surcharge de l'opérateur == pour les DirectionVector (test)
	 * @param lhs DirectionVector à gauche
	 * @param rhs  DirectionVector à droite
	 * @return Egalité des DirectionVector
	 */
	bool const operator==( Othello::Board::DirectionVector& lhs, Othello::Board::DirectionVector& rhs );

#endif
