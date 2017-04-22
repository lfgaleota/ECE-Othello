#ifndef _ECE_OTHELLO_UI_GAME_HPP_
	#define _ECE_OTHELLO_UI_GAME_HPP_

	#include "../../board/gameboard.hpp"
	#include "../../players/player.hpp"

	/**
	 * @namespace Othello
	 * @details Espace de nommage du jeu.
	 */
	namespace Othello {
		/**
		 * @namespace UI
		 * @details Espace de nommage des interfaces du jeu.
		 */
		namespace UI {
			/**
			 * @class Game
			 * @brief Interface du jeu
			 * @details Cette classe est une interface contenant les fonctions communes aux interfaces de jeu.
			 */
			class Game {
				protected:
					const Othello::Board::GameBoard::punArray m_board;
					const std::vector<Othello::Players::Player*>& m_players;
					const std::vector<Othello::Players::Player*>::iterator& m_currentPlayer;
					Othello::Board::Tree::ValidMoveNode* m_tree = nullptr;

				public:
					/**
					 * @brief Constructeur de l'interface de jeu
					 * @details Initialise l'interface de jeu, lorsqu'il démarre.
					 * @param[in] board Pointeur vers le plateau de jeu
					 * @param[in] players Référence vers l'ensemble des joueurs
					 * @param[in] currentPlayer Référence vers le joueur actuel
					 */
					Game( const Othello::Board::GameBoard::punArray board, const std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& currentPlayer ) : m_board( board ), m_players( players ), m_currentPlayer( currentPlayer ) {};

					/**
					 * @brief Destructeur de l'interface de jeu
					 */
					virtual ~Game() {};

					/**
					 * @brief Affichage d'une erreur
					 * @details Informe l'utilisateur d'une erreur au sein du programme. Bloque le programme en attendant une action de l'utilisateur.
					 * @param msg Message d'erreur
					 */
					virtual void showError( std::string msg ) = 0;

					/**
					 * @brief Affichage d'un message d'information
					 * @details Informe l'utilisateur d'une erreur au sein du programme. Non bloquant.
					 * @param msg Message d'erreur
					 */
					virtual void inform( std::string msg ) = 0;

					/**
					 * @brief Informer qu'un joueur ne peut pas jouer
					 * @param player Joueur qui ne peut pas jouer
					 */
					virtual void informNoAvailableMoves( Othello::Players::Player* player ) = 0;

					/**
					 * @brief	Évènement demande de coup
					 * @details	Fonction appelée lorsque le jeu a besoin du coup voulu par le joueur humain. Lâche une exception #no_selected_move si le coup n'est pas sélectionné.
					 * @return	Coup joué/demandé par le joueur
					 */
					virtual Othello::Board::Move getMove() = 0;

					/**
					 * @brief	Demandeur de rendue
					 * @details	Demande à l'interface de procéder à ses fonctions.
					 */
					virtual void render() = 0;

					/**
					 * @brief	Évènement début de tour
					 * @details	Fonction appelée au début du tour d'un joueur, avant toute chose.
					 * @param[in] player Joueur actuel
					 */
					virtual void playerTurnBegin( Othello::Players::Player* player ) = 0;

					/**
					 * @brief	Évènement fin de tour
					 * @details	Fonction appelée à la fin du tour d'un joueur, après toutes ses actions.
					 * @param[in] player Joueur actuel
					 */
					virtual void playerTurnEnd( Othello::Players::Player* player ) = 0;

					/**
					 * @brief	Écran de victoire
					 * @details	Affiche un écran de victoire pour le joueur gagnant.
					 * @param[in] player Joueur gagnant
					 */
					virtual void victory( Othello::Players::Player* player ) = 0;


					/**
					 * @brief	Mutateur d'arbre des coups parcourus
					 * @details	Définie l'arbre qui sera affiché dans la fonction de parcours d'arbre.
					 * @param[in] head Pointeur vers le noeud parent de l'arbre
					 */
					void setTree( Othello::Board::Tree::ValidMoveNode* head ) {
						m_tree = head;
					}
			};
		}
	}

#endif
