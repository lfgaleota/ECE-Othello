#ifndef ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP
	#define ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP

	#include <vector>
	#include "../../board/tree/validmovenode.hpp"
	#include "../../../../cli/cli.hpp"

	namespace Othello {
		namespace UI {
			namespace Games {
				class CLIValidMoveTreeViewer {
					private:
						Othello::Board::Tree::ValidMoveNode* m_tree;
						std::vector<unsigned int> m_cursors;
						std::vector<const Othello::Board::Tree::ValidMoveNode*> m_nodes;
						Functions::CLI cli;
						unsigned char x = 0;

					public:
						CLIValidMoveTreeViewer( Othello::Board::Tree::ValidMoveNode* m_tree, unsigned int depth );
						void render();
						void renderColumn( const Othello::Board::Tree::ValidMoveNode* node, unsigned int depth );
						void renderNode( const Othello::Board::GameBoard* ref, int eval, unsigned int offset_x, unsigned int offset_y );
				};
			}
		}
	}


#endif //ECE_OTHELLO_UI_GAMES_CLIVALIDMOVETREEVIEWER_HPP
