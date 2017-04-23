#ifndef _ECE_OTHELLO_ALGORITHMS_HEURISTICS_HPP_
	#define _ECE_OTHELLO_ALGORITHMS_HEURISTICS_HPP_

	#include "../board/gameboard.hpp"

	/**
	 * @namespace Othello
	 * @details Espace de nommage du jeu.
	 */
	namespace Othello {
		/**
		 * @namespace Algorithms
		 * @details Espace de nommage regroupant les quelques algorithmes du jeu, en dehors de ceux du plateau et de l'interface.
		 */
		namespace Algorithms {
		    /**
		     * @class Heuristics
		     * @brief Classe des heuristiques
		     * @details Comporte les méthodes d'heuristiques utilisée dans le jeu.
		     */
			class Heuristics {
				public:
					typedef int (*evalFunctionType)( Othello::Board::GameBoard* ref, Othello::Board::Pun::Colors color, Othello::Board::Pun::Colors opposite );

				    static const int weightTable[ Othello::Board::sizeEdge ][ Othello::Board::sizeEdge ];

					/**
					 * @brief Heuristique simple
					 * @details Fonction d'heuristique simple qui choisit le meilleur coup sur le critère du nombre de pièces retournées.
					 * @return 0
					 */
					static int simple( Othello::Board::GameBoard* ref, Othello::Board::Pun::Colors color, Othello::Board::Pun::Colors opposite );

					/**
					 * @brief Heuristique avancée
					 * @details Fonction d'heuristique prenant en compte un certain nombre de facteursq pour calculer la valuer du plateau, comme la mobilité ou la parité des pièces
					 * @return 0
					 */
					static int normale( Othello::Board::GameBoard* ref, Othello::Board::Pun::Colors color, Othello::Board::Pun::Colors opposite );
			};
		}
	}

#endif
