#ifndef ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP
	#define ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP

	#include <allegro.h>
	#ifdef ALLEGRO_WINDOWS
		#include <winalleg.h>
	#endif
	#include <loadpng.h>
	#include <jpgalleg.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <alleggl.h>
	#include <vector>
	#include "../../board/tree/validmovenode.hpp"

	#define VIEWER_MARGIN 2
	#define VIEWER_CASE_SIZE 10
	#define VIEWER_CASE_COLOR makecol( 0, 150, 0 )
	#define VIEWER_CASE_MARGIN 1
	#define VIEWER_PUN_COLOR_WHITE makecol( 255, 255, 255 )
	#define VIEWER_PUN_COLOR_BLACK makecol( 0, 0, 0 )
	#define VIEWER_BORDER_SIZE 2
	#define VIEWER_BORDER_COLOR_SELECTED makecol( 255, 0, 0 )
	#define VIEWER_BORDER_COLOR makecol( 0, 0, 0 )
	#define VIEWER_TEXT_COLOR makecol( 255, 255, 255 )
	#define VIEWER_TEXT_BGCOLOR makecol( 0, 0, 0 )

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
			     * @class AllegroValidMoveTreeViewer
			     * @brief Afficheur d'arbre de coups graphique
			     * @details Cet afficheur affiche l'abre un noeud à la fois: on sélectionne avec le curseur, le noeud dont on souhaite voir afficher les fils dans la colonne suivante.
			     */
				class AllegroValidMoveTreeViewer {
					private:
						Othello::Board::Tree::ValidMoveNode** m_tree;
						std::vector<unsigned int> m_cursors;
						std::vector<const Othello::Board::Tree::ValidMoveNode*> m_nodes;
						BITMAP* m_page;
						unsigned char x = 0;
						unsigned int m_depth;
						bool m_keyPressed = false;

						/**
						 * @brief Affichage de l'arbre
						 */
						void renderTree();

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
						 * @param showCursor Affichage du cursuer
						 * @param selected Affichage en surimpression du curseur
						 */
						void renderNode( const Othello::Board::GameBoard* ref, int eval, unsigned int offset_x, unsigned int offset_y, bool showCursor, bool selected );

					public:
						bool opened = false;

						/**
						 * @brief Constructeur par défaut
						 * @details Permet d'avoir un objet résidant sans pour autant fournir les arguments
						 */
						AllegroValidMoveTreeViewer();

						/**
						 * @brief Constructeur
						 * @param m_tree Arbre à considérer
						 * @param depth Profondeur de l'arbre
						 * @param page Bitmap vers laquelle afficher l'arbre
						 */
						AllegroValidMoveTreeViewer( Othello::Board::Tree::ValidMoveNode** m_tree, unsigned int depth, BITMAP* page );

						/**
						 * @brief Afficheur de l'arbre
						 */
						void render();
				};
			}
		}
	}


#endif //ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP
