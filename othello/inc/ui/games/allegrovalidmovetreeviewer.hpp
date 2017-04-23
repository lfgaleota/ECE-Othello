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

	/// \namespace Othello
	namespace Othello {
		/// \namespace UI
		namespace UI {
		    /// \namespace Games
			namespace Games {
			    /// \class AllegroValidMoveTreeViewer
			    /// \brief class permettant de faire l'affichage de l'arbre des possibilitÚs concernant les IA
				class AllegroValidMoveTreeViewer {
					private:
						Othello::Board::Tree::ValidMoveNode** m_tree;
						std::vector<unsigned int> m_cursors;
						std::vector<const Othello::Board::Tree::ValidMoveNode*> m_nodes;
						BITMAP* m_page;
						unsigned char x = 0;
						unsigned int m_depth;
						bool m_keyPressed = false;

						/// \fn renderTree
                        /// \param {no parameters}
						void renderTree();
						/// \fn renderColumn
                        /// \param {node,depth}
						void renderColumn( const Othello::Board::Tree::ValidMoveNode* node, unsigned int depth );
						/// \fn renderNode
                        /// \param {eval,offset_x,offset_y,showCursor,selected}
						void renderNode( const Othello::Board::GameBoard* ref, int eval, unsigned int offset_x, unsigned int offset_y, bool showCursor, bool selected );

					public:
						bool opened = false;

						/// \fn default constructor
                        /// \param {no parameters}
						AllegroValidMoveTreeViewer();
						/// \fn overload constructor
                        /// \param {m_tree,depth,page}
						AllegroValidMoveTreeViewer( Othello::Board::Tree::ValidMoveNode** m_tree, unsigned int depth, BITMAP* page );
						/// \fn render
                        /// \param {no parameters}
						void render();
				};
			}
		}
	}


#endif //ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP
