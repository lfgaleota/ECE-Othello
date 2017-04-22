#ifndef _ECE_OTHELLO_PLAYERS_HUMAN_HPP_
	#define _ECE_OTHELLO_PLAYERS_HUMAN_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "uiplayer.hpp"

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
			 * @class Human
			 * @brief Classe représentrant un joueur humain
			 * @details Utilise l'UI pour demander les coups du joueur.
			 */
			class Human : public UIPlayer {
				public:
					/**
					 * @brief Constructeur
					 * @param name Nom du joueur
					 * @param color Couleur de pion du joueur
					 */
					Human( std::string name, Othello::Board::Pun::Colors color );

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

					/**
					 * @brief Accesseur de type de joueur
					 * @return Type de joueur
					 */
					Type getType();
			};
		}
	}

#endif
