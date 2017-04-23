#ifndef _ECE_OTHELLO_PLAYERS_RANDOMIA_HPP_
	#define _ECE_OTHELLO_PLAYERS_RANDOMIA_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include <random>
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
			 * @class RandomAI
			 * @brief Classe représentrant une IA aléatoire
			 * @details Cette IA joue des coups aléatoires parmi ceux possibles.
			 */
			class RandomAI : public UIPlayer {
				public:
					/**
					 * @brief Constructeur
					 * @param name Nom du joueur
					 * @param color Couleur de pion du joueur
					 */
					RandomAI( std::string name, Othello::Board::Pun::Colors color );

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

					/**
					 * @brief Informateur d'arrêt de jeu
					 * @details Fonction appelée quand le jeu quitte, pour permettre à la classe joueur de quitter proprement si besoin.
					 */
					void quit();
			};
		}
	}

#endif
