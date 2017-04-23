#ifndef _ECE_OTHELLO_ALGORITHMS_MINIMAX_HPP_
	#define _ECE_OTHELLO_ALGORITHMS_MINIMAX_HPP_

	#include <algorithm>
	#include <thread>
	#include "../board/gameboard.hpp"
	#include "../board/tree/validmovenode.hpp"
	#include "heuristics.hpp"

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
			 * @class MiniMax
			 * @details Implémentation de l'algorithme AlphaBeta
			 */
			class MiniMax {
				private:
					Othello::Board::ValidMove* m_foundMove = nullptr;
					Othello::Board::Pun::Colors m_color, m_oppositeColor;
					Heuristics::evalFunctionType m_evalFn;

					/**
					 * @brief Calcul du max
					 * @param ref Noeud de référence
					 * @param skipped Indique si la profondeur précédente a été passée (pas de coups)
					 * @param depth Profondeur actuelle
					 * @return Valeur max du noeud
					 */
					int max( Othello::Board::Tree::ValidMoveNode* ref, bool skipped, unsigned int depth );

					/**
					 * @brief Calcul du min
					 * @param ref Noeud de référence
					 * @param skipped Indique si la profondeur précédente a été passée (pas de coups)
					 * @param depth Profondeur actuelle
					 * @return Valeur min du noeud
					 */
					int min( Othello::Board::Tree::ValidMoveNode* ref, bool skipped, unsigned int depth );

					/**
					 * @brief Lanceur de max
					 * @details Utilisée par le thread pour lancer l'algorithme
					 * @param ref Noeud de référence
					 * @param val Pointeur vers l'endroit où stocker le max du noeud
					 */
					void runMax( Othello::Board::Tree::ValidMoveNode* ref, int* val );

				public:
					static const int MIN;
					static const int DRAW;
					static const int MAX;
					static const int DEPTH;

					/**
					 * @brief Lancer d'AlphaBeta
					 * @param ref Plateau de départ
					 * @param head Noeud maître à utiliser
					 * @param color Couleur du pion ami
					 * @param evalFn Pointeur vers la fonction d'évaluation à utiliser
					 */
					MiniMax( Othello::Board::GameBoard* ref, Othello::Board::Tree::ValidMoveNode* head, Othello::Board::Pun::Colors color, Heuristics::evalFunctionType evalFn );

					/**
					 * @brief Récupérateur de coup choisie
					 * @return Coup choisie
					 */
					Othello::Board::ValidMove* getResult();
			};
		}
	}

#endif
