#ifndef ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP
	#define ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP

	#include <vector>
	#include "../../board/tree/validmovenode.hpp"
	#include "../../../../cli/cli.hpp"

    /// \namespace Othello
	namespace Othello {
	    /// \namespace UI
		namespace UI {
		    /// \namespace Games
			namespace Games {
			    /// \class CLIValidMoveTreeViewer
			    /// \brief class permettant de faire l'affichage de l'arbre des possibilités concernant les IA dans l'user interface
				class CLIValidMoveTreeViewer {
					private:
						Othello::Board::Tree::ValidMoveNode* m_tree;
						std::vector<unsigned int> m_cursors;
						std::vector<const Othello::Board::Tree::ValidMoveNode*> m_nodes;
						Functions::CLI cli;
						unsigned char x = 0;

					public:
						/// \fn overload constructor
                        /// \param {m_tree,depth}
						CLIValidMoveTreeViewer( Othello::Board::Tree::ValidMoveNode* m_tree, unsigned int depth );
						/// \fn render
                        /// \param {no parameters}
						void render();
						/// \fn renderColumn
                        /// \param {node,depth}
						void renderColumn( const Othello::Board::Tree::ValidMoveNode* node, unsigned int depth );
						/// \fn renderNode
                        /// \param {gameboard ref,eval,offset_x,offset_y}
						void renderNode( const Othello::Board::GameBoard* ref, int eval, unsigned int offset_x, unsigned int offset_y );
				};
			}
		}
	}


#endif //ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP
