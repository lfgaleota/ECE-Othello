#ifndef _ECE_OTHELLO_PLAYERS_PLAYER_HPP_
	#define _ECE_OTHELLO_PLAYERS_PLAYER_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "../board/pun.hpp"
	#include "../board/move.hpp"
	#include "../board/gameboard.hpp"

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
			 * @class Player
			 * @brief Classe représentrant un joueur
			 * @details L'interface Player représente un joueur quelconque du jeu, que cela soit un humain, une IA ou autre. Elle définie un ensemble de fonctions communes qui fonctionneront de la même manière peu importe le joueur.
			 */
			class Player {
				protected:
					std::string m_name; /*! < Nom du joueur */
					Othello::Board::Pun::Colors m_color; /*! < Couleur de pion du joueur */
					bool m_canPlay = true; /*! < Définie si un joueur peut jouer */
					unsigned char m_punCount = 0; /*! < Nombre de pions à la fin de la partie* */
					Othello::Board::GameBoard* m_board; /*! < Pointeur vers le plateau de jeu, utile pour les IA */

				public:
					/**
					 * @enum Type
					 * @brief Types de joueur
					 */
					enum Type {
						Human, /*! < Joueur humain */
						RandomAI, /*! < IA aléatoire */
						SimpleAI, /*! < IA simple */
						EnhancedAI /*! < IA normale */
					};

					/**
					 * @brief Constructeur
					 * @param name Nom du joueur
					 * @param color Couleur de pion du joueur
					 */
					Player( std::string name, Othello::Board::Pun::Colors color );

					/**
					 * @brief Destructeur
					 */
					 virtual ~Player();

					/**
					 * @brief Accesseur de nom
					 * @return Nom du joueur
					 */
					const std::string& getName() const;

					/**
					 * @brief Accesseur de couleur de pion
					 * @return Couleur de pion du joueur
					 */
					Othello::Board::Pun::Colors getColor() const;

					/**
					 * @brief Accesseur de possibilité de jouer
					 * @return Possibilité de jouer du joueur
					 */
					bool canPlay() const;

					/**
					 * @brief Accesseur du nombre de pions
					 * @return Nombre de pions du joueur (à la fin de la partie)
					 */
					unsigned char getPunCount() const;

					/**
					 * @brief Mutateur du nombre de pions
					 * @param punCount Nombre de pions du joueur (à la fin de la partie)
					 */
					void setPunCount( unsigned char punCount );

					/**
					 * @brief Mutateur de possibilité de joueur
					 * @details Indique que le joueur peut jouer.
					 */
					void setCanPlay();

					/**
					 * @brief Mutateur d'impossibilité de joueur
					 * @details Indique que le joueur ne peut pas jouer.
					 */
					void setCannotPlay();

					/**
					 * @brief Mutateur de poineur de plateau
					 * @details À appelé au plus tôt, définie le plateau qui sera utilisé par le joueur.
					 * @param board Pointeur vers plateau de jeu
					 */
					void setBoard( Othello::Board::GameBoard* board );

					/**
					 * @brief Début de tour
					 * @details Informe le joueur que son tour démarre.
					 */
					virtual void turnBegin() = 0;

					/**
					 * @brief Fin de tour
					 * @details Informe le joueur que son tour est terminé.
					 */
					virtual void turnEnd() = 0;

					/**
					 * @brief Informateur de coup indisponible
					 * @brief Indique au joueur qu'il ne peut pas jouer car il n'a pas de coup possible.
					 */
					virtual void noAvailableMoves() = 0;

					/**
					 * @brief Informateur d'erreur
					 * @param message Message d'erreur
					 */
					virtual void error( std::string message ) = 0;

					/**
					 * @brief Récupérateur de mouvement choisi
					 * @details Demande au joueur le mouvement qu'il souhaite jouer.
					 * @return Mouvement choisi
					 */
					virtual Othello::Board::Move getMove() = 0;

					/**
					 * @brief Accesseur de type de joueur
					 * @return Type de joueur
					 */
					 virtual Type getType() = 0;

					/**
					 * @brief Informateur d'arrêt de jeu
					 * @details Fonction appelée quand le jeu quitte, pour permettre à la classe joueur de quitter proprement si besoin.
					 */
					virtual void quit() = 0;

					/**
					 * @brief Vérificateur de type
					 * @ëetails Vérifie si l'entier fournit peut être caster de manière sécurisée vers une énumération #Type.
					 * @return Validité de l'entier
					 */
					static bool typeCheck( int typeInt );
			};
		}
	}

#endif
