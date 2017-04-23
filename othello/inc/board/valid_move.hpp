#ifndef _ECE_OTHELLO_BOARD_VALIDMOVE_HPP_
#define _ECE_OTHELLO_BOARD_VALIDMOVE_HPP_

	#include <list>
	#include "move.hpp"
	#include "direction_vector.hpp"

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
			 * @struct Move
			 * @brief Structure représentant un mouvement valide, avec ses directions associés
			 */
			struct ValidMove : public Move {
				std::list<DirectionVector> directions; /*! < Directions associées */

				/**
				 * @brief Constructeur
				 * @param x Coordonnée en abscisse
				 * @param y Coordonnée en ordonnée
				 */
				ValidMove( unsigned char x, unsigned char y );

				/**
				 * @brief Constructeur par copie de Move
				 * @param move Mouvement de référence
				 */
				ValidMove( const Move& move );

				/**
				 * @brief Ajouteur de direction
				 * @param dvec Ajoute uen direction
				 */
				inline void addDirection( DirectionVector dvec ) {
					directions.push_back( dvec );
				}
			};
		}
	}

#endif
