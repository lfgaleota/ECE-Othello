#ifndef _ECE_OTHELLO_BOARD_TREE_VALIDMOVENODE_HPP_
	#define _ECE_OTHELLO_BOARD_TREE_VALIDMOVENODE_HPP_

	#include <list>
	#include <vector>
	#include "../gameboard.hpp"

	namespace Othello {
		namespace Board {
			namespace Tree {
				class ValidMoveNode {
					private:
						Othello::Board::GameBoard* m_board;
						std::list<ValidMoveNode> m_nextNodes;

					public:
						ValidMoveNode( Othello::Board::GameBoard* board );
						~ValidMoveNode();

						void compute( Pun::Colors color, unsigned char depth );
						const Othello::Board::GameBoard* getBoard() const;
						const std::list<ValidMoveNode>& getNextNodes() const;
				};
			}
		}
	}

#endif
