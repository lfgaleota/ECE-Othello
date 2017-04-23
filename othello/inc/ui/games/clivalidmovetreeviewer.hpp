#ifndef ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP
	#define ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP

	#include <vector>
	#include "../../board/tree/validmovenode.hpp"
	#include "../../../../cli/cli.hpp"

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
				 * @class CLIValidMoveTreeViewer
				 * @brief Afficheur d'arbre de coups console
				 * @details Cet afficheur affiche l'abre un noeud à la fois: on sélectionne avec le curseur, le noeud dont on souhaite voir afficher les fils dans la colonne suivante.
				 */
				class CLIValidMoveTreeViewer {
					private:
						Othello::Board::Tree::ValidMoveNode* m_tree;
						std::vector<unsigned int> m_cursors;
						std::vector<const Othello::Board::Tree::ValidMoveNode*> m_nodes;
						Functions::CLI cli;
						unsigned char x = 0;

						/**
						 * @brief Affichage des colonnes
						 * @param node Noeud associé
						 * @param depth Profondeur à laquelle on se trouve
						 */
						void renderColumn( const Othello::Board::Tree::ValidMoveNode* node, unsigned int depth );

						/**
						 * @brief Affichage de noeud
						 * @param ref Noeud à afficher
						 * @param eval Valeur d'évaluation
						 * @param offset_x Position en abscisse de son emplacement
						 * @param offset_y  Position en ordonnée de son emplacement
						 */
						void renderNode( const Othello::Board::GameBoard* ref, int eval, unsigned int offset_x, unsigned int offset_y );

					public:
						/**
						 * @brief Constructeur
						 * @param m_tree Arbre à considérer
						 * @param depth Profondeur de l'arbre
						 */
						CLIValidMoveTreeViewer( Othello::Board::Tree::ValidMoveNode* m_tree, unsigned int depth );

						/**
						 * @brief Afficheur de l'arbre
						 * @etails Prends le pas sur l'exécution normal du code, bloque l'utilisateur tant qu'il ne l'a pas quitté.
						 */
						void render();
				};
			}
		}
	}


#endif //ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP
