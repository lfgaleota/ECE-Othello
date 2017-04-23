#ifndef _ECE_OTHELLO_BOARD_MOVE_HPP_
	#define _ECE_OTHELLO_BOARD_MOVE_HPP_

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
		    /**
		     * @struct Move
		     * @brief Représente un déplacement
		     */
			struct Move {
				const unsigned char x; /*! < Coordonnée en abscisse */
				const unsigned char y; /*! < Coordonnée en ordonnée */
				const Pun::Colors color; /*! < Couleur associée */

				/**
				 * @brief Constructeur
				 * @param x Coordonnée en abscisse
				 * @param y Coordonnée en ordonnée
				 */
				Move( unsigned char x, unsigned char y );

				/**
				 * @brief Constructeur avec couleur
				 * @param x Coordonnée en abscisse
				 * @param y Coordonnée en ordonnée
				 * @param color Couleur associée
				 */
				Move( unsigned char x, unsigned char y, Pun::Colors color );

				/**
				 * @brief Constructeur par copie
				 * @param move Mouvement de référence
				 */
				Move( const Move &move );
			};
		}
	}

	/**
	 * @brief Surcharge de l'opérateur == pour les Move (test)
	 * @param lhs Move à gauche
	 * @param rhs  Move à droite
	 * @return Egalité des Move
	 */
	bool operator==( const Othello::Board::Move& lhs, const Othello::Board::Move& rhs );


	/**
	 * @brief Surcharge de l'opérateur < pour les Move (infériorité)
	 * @param lhs Move à gauche
	 * @param rhs  Move à droite
	 * @return Infériorité du Move de gauche par rapport au droit
	 */
	bool operator<( const Othello::Board::Move& lhs, const Othello::Board::Move& rhs );

#endif
