#ifndef _ECE_OTHELLO_PLAYERS_ENHANCEDAI_HPP_
	#define _ECE_OTHELLO_PLAYERS_ENHANCEDAI_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include <exception>
	#include <atomic>
	#include "uiplayer.hpp"
	#include "../algorithms/alphabeta.hpp"
	#include "../algorithms/minimax.hpp"

	/**
	 * @namespace Othello
	 * @details Espace de nommage du jeu.
	 */
	namespace Othello {
		/**
		 * @namespace Players
		 * @details Espace de nommage regroupant les différentes classes de joueurs.
		 */
		namespace Players {
			/**
			 * @class EnhancedAI
			 * @brief Classe représentrant une IA améliorée
			 * @details Cette IA utilise l'algorithme MiniMax, combinée avec une fonction d'heuristique, pour trouver le meilleur coup. Elle stocke l'arbre des coups parcourus une fois l'algorithme terminé et le passe à l'interface pour pouvoir l'afficher.
			 */
			class EnhancedAI : public UIPlayer {
				private:
					Othello::Board::Tree::ValidMoveNode m_tree; /*!< Arbre des coups parcourus */
					std::atomic<bool> m_done; /*! < Indicateur de fin de calcul */

				public:
					/**
					 * @brief Constructeur
					 * @param name Nom du joueur
					 * @param color Couleur de pion du joueur
					 */
					EnhancedAI( std::string name, Othello::Board::Pun::Colors color );

					/**
					 * @brief Récupérateur de mouvement choisi
					 * @details Demande au joueur le mouvement qu'il souhaite jouer.
					 * @return Mouvement choisi
					 */
					Othello::Board::Move getMove();

					/**
					 * @brief Début de tour
					 * @details Informe le joueur que son tour démarre.
					 */
					void turnBegin();

					/**
					 * @brief Fin de tour
					 * @details Informe le joueur que son tour est terminé.
					 */
					void turnEnd();
			};
		}
	}

#endif
