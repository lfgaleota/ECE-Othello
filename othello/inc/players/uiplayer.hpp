#ifndef _ECE_OTHELLO_PLAYER_UIPLAYER_HPP_
#define _ECE_OTHELLO_PLAYER_UIPLAYER_HPP_

	#include "player.hpp"
	#include "../ui/games/gameui.hpp"

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
			 * @class UIPlayer
			 * @brief Classe représentrant un joueur utilisant l'UI
			 * @details Cette classe est une constrution pour éviter les dépendances cycliques en Joueur et Interface. Chaque Joueur a besoin d'intéragir avec l'interface, pour au moins informer la personne de ce qu'il se passe.
			 */
			class UIPlayer : public Player {
				protected:
					Othello::UI::Game* m_ui; /*!< Pointeur vers interface */

				public:
					/**
					 * @brief Constructeur
					 * @param name Nom du joueur
					 * @param color Couleur de pion du joueur
					 */
					UIPlayer( std::string name, Othello::Board::Pun::Colors color );


					/**
					 * @brief Mutateur de l'UI dans la classe UIPlayer
					 * @details Définie l'UI utilisé par l'objet
					 * @param m_ui Pointeur vers objet d'interface
					 */
					void setUI( Othello::UI::Game* m_ui );

					/**
					 * @brief Début de tour
					 * @details Informe le joueur que son tour démarre.
					 */
					virtual void turnBegin();

					/**
					 * @brief Fin de tour
					 * @details Informe le joueur que son tour est terminé.
					 */
					virtual void turnEnd();

					/**
					 * @brief Informateur de coup indisponible
					 * @brief Indique au joueur qu'il ne peut pas jouer car il n'a pas de coup possible.
					 */
					void noAvailableMoves();

					/**
					 * @brief Informateur d'erreur
					 * @param message Message d'erreur
					 */
					void error( std::string message );
			};
		}
	}

#endif
