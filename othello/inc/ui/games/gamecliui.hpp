#ifndef _ECE_OTHELLO_UI_GAMES_CLI_HPP_
	#define _ECE_OTHELLO_UI_GAMES_CLI_HPP_


	#include <iostream>
	#include <iomanip>
	#include <fstream>
	#include <sstream>
	#include "../../board/gameboard.hpp"
	#include "../../players/player.hpp"
	#include "gameui.hpp"
	#include "../../../../cli/cli.hpp"
	#include "../../../../cli/menu/menu.hpp"
	#include "clivalidmovetreeviewer.hpp"

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
			 * @namespace Games
			 * @details Espace de nommage des interfaces de jeu du jeu.
			 */
			namespace Games {
				/**
				 * @class CLI
				 * @brief Classe d'interface console
				 */
				class CLI : public Othello::UI::Game {
					private:
						Functions::CLI cli;
						std::vector<std::string> m_displayMatrix;
						Othello::Board::GameBoard& m_oboard;
						unsigned char x = 0, y = 0;

						/**
						 * @brief	Affichage de l'interface
						 * @details	Affiche l'ensemble de l'interface, plateau et informations des joueurs.
						 */
						void display();

						/**
						 * @brief	Affichage du plateau
						 * @details	Affiche le plateau de jeu à l'écran, avec le fond précalculé.
						 */
						void displayMatrix();

						/**
						 * @brief	Affichage des joueurs
						 * @details	Affiche les informations des joueurs à l'écran. Ici, leur nom est affiché, et le nom du joueur actuel est affiché en surimpression.
						 */
						void displayPlayers();

						/**
						 * @brief	Affichage du nombre de pions sur le plateau
						 */
						void displayCounts();

						/**
						 * @brief Affichage du nombre de pions d'une couleur du plateau
						 * @param color Couleur à utiliser
						 */
						void displayCount( Othello::Board::Pun::Colors color );

						/**
						 * @brief	Génération d'un fond de plateau
						 * @details	Construit, à partir de la taille de la matrice, un fond de plateau destiné à être affiché par l'interface.
						 *         	Cette fonction ne prend et renvoie rien. Elle utilise, en revanche, le paramètre sizeEdge de #Board, et remplie l'attribut #m_displaymatrix avec un ensemble de chaînes de caractères prêtes à afficher.
						 */
						void loadDisplayMatrix();

						/**
						 * @brief	Affichage d'une pièce
						 * @details	Affiche une pièce du plateau
						 * @param[in] piece Pièce à afficher
						 * @param[in] offsetX Coordonnée en abscisse de l'endroit où doit être affiché la pièce
						 * @param[in] offsetY Coordonnée en ordonnée de l'endroit où doit être affiché la pièce
						 */
						void showPiece( Othello::Board::Pun::Colors color, unsigned int offsetX, unsigned int offsetY );

						/**
						 * @brief	Met en valeur une pièce
						 * @details	Permet de mettre en valeur un emplacement du plateau aux coordonnées indiquées, avec la couleur fournie.
						 * @param[in] x Coordonnée en abscisse de l'emplacement
						 * @param[in] y Coordonnée en ordonnée de l'emplacement
						 * @param[in] color Couleur de surimpression
						 */
						void highlightSelectedPiece( unsigned char x, unsigned char y, unsigned char color );

						/**
						 * @brief Écran de pause
						 * @details Demande au joueur s'il souahite arrếter la partie. Lance une exception exit_game (cf #Exceptions) lorsque le joueur souhaite quitter le jeu.
						 */
						void pauseMenu();

					public:
						/**
						 * @brief Constructeur de l'interface de jeu
						 * @details Initialise l'interface de jeu, lorsqu'il démarre.
						 * @param[in] oboard Référence vers la classe #Board de jeu
						 * @param[in] board Pointeur vers le plateau de jeu
						 * @param[in] players Référence vers l'ensemble des joueurs
						 * @param[in] currentPlayer Référence vers le joueur actuel
						 */
						CLI( Othello::Board::GameBoard& oboard, const Othello::Board::GameBoard::punArray board,
						     const std::vector<Othello::Players::Player*>& players,
						     std::vector<Othello::Players::Player*>::iterator& currentPlayer );

						/**
						 * @brief Destructeur de l'interface de jeu
						 */
						~CLI();

						/**
						 * @brief Affichage d'une erreur
						 * @details Informe l'utilisateur d'une erreur au sein du programme. Bloque le programme en attendant une action de l'utilisateur.
						 * @param msg Message d'erreur
						 */
						void showError( std::string msg );

						/**
						 * @brief Informer qu'un joueur ne peut pas jouer
						 * @param player Joueur qui ne peut pas jouer
						 */
						void informNoAvailableMoves( Othello::Players::Player* player );

						/**
						 * @brief Affichage d'un message d'information
						 * @details Informe l'utilisateur d'une erreur au sein du programme. Non bloquant.
						 * @param msg Message d'erreur
						 */
						void inform( std::string msg );

						/**
						 * @brief	Évènement demande de coup
						 * @details	Fonction appelée lorsque le jeu a besoin du coup voulu par le joueur humain. Lâche une exception #no_selected_move si le coup n'est pas sélectionné.
						 * @return	Coup joué/demandé par le joueur
						 */
						Othello::Board::Move getMove();

						/**
						 * @brief	Demandeur de rendue
						 * @details	Demande à l'interface de procéder à ses fonctions.
						 */
						void render();

						/**
						 * @brief	Évènement début de tour
						 * @details	Fonction appelée au début du tour d'un joueur, avant toute chose.
						 * @param[in] player Joueur actuel
						 */
						void playerTurnBegin( Othello::Players::Player* player );

						/**
						 * @brief	Évènement fin de tour
						 * @details	Fonction appelée à la fin du tour d'un joueur, après toutes ses actions.
						 * @param[in] player Joueur actuel
						 */
						void playerTurnEnd( Othello::Players::Player* player );

						/**
						 * @brief	Écran de victoire
						 * @details	Affiche un écran de victoire pour le joueur gagnant.
						 * @param[in] player Joueur gagnant
						 */
						void victory( Othello::Players::Player* player );
				};
			}
		}
	}

#endif
