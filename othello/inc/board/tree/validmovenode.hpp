#ifndef _ECE_OTHELLO_BOARD_TREE_VALIDMOVENODE_HPP_
	#define _ECE_OTHELLO_BOARD_TREE_VALIDMOVENODE_HPP_

	#include <list>
	#include <vector>
	#include "../gameboard.hpp"

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
			 * @namespace Board
			 * @details Espace de nommage regroupant les éléments liés au graphe des possibilités
			 */
			namespace Tree {
			    /**
			     * @class ValidMoveNode
			     * @brief Noeud de l'arbre des possibilités
			     */
				class ValidMoveNode {
					friend class Othello::Algorithms::MiniMax;
					friend class Othello::Algorithms::AlphaBeta;

					private:
						Othello::Board::GameBoard* m_board;
						Othello::Board::ValidMove* m_validMove;
						std::list<ValidMoveNode> m_nextNodes;
						int m_eval = 0;

					public:
						/**
						 * @brief Constructeur de noeud parent
						 * @param board Plateau de référence
						 */
						ValidMoveNode( Othello::Board::GameBoard* board );
						/**
						 * @brief Constructeur de noeud enfant
						 * @param board Plateau de référence
						 * @param validMove Mouvement valide associé
						 */
						ValidMoveNode( Othello::Board::GameBoard* board, Othello::Board::ValidMove* validMove );
						/**
						 * @brief Destructeur
						 */
						~ValidMoveNode();

						/**
						 * @brief Calculateur d'arbre
						 * @param color Couleur de pion ami
						 * @param depth Profondeur souhaitée
						 */
						void compute( Othello::Board::Pun::Colors color, unsigned char depth );
						/**
						 * @brief Préparateur d'étage inférieur
						 * @details Permet de préparer la profonduer inférieur enfante aux calculs
						 * @param color Couleur de pion ami
						 */
						void prepareBottomStage( Othello::Board::Pun::Colors color );
						/**
						 * @brief Accesseur de plateau
						 * @return Pointeur constant vers le plateau associé
						 */
						const Othello::Board::GameBoard* getBoard() const;
						/**
						 * @brief Accesseur des noeuds enfants
						 * @return Référence vers la liste des noeuds enfants
						 */
						const std::list<ValidMoveNode>& getNextNodes() const;
						/**
						 * @brief Accesseur de coup valide
						 * @return Pointeur vers le coup valide associé
						 */
						ValidMove* getValidMove() const;
						/**
						 * @brief Accesseur de valeur d'évaluation
						 * @return Valeur d'évaluation du noeud
						 */
						int getEval() const;
				};
			}
		}
	}

#endif
