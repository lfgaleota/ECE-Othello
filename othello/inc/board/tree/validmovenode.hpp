#ifndef _ECE_OTHELLO_BOARD_TREE_VALIDMOVENODE_HPP_
	#define _ECE_OTHELLO_BOARD_TREE_VALIDMOVENODE_HPP_

	#include <list>
	#include <vector>
	#include "../gameboard.hpp"

	namespace Othello {
		namespace Board {
			namespace Tree {
			    /// \class ValidMoveNode validmovenode.hpp
				class ValidMoveNode {
					friend class Othello::Algorithms::MiniMax;

					private:
						Othello::Board::GameBoard* m_board;
						Othello::Board::ValidMove* m_validMove;
						std::list<ValidMoveNode> m_nextNodes;

					public:
						ValidMoveNode( Othello::Board::GameBoard* board );
						ValidMoveNode( Othello::Board::GameBoard* board, Othello::Board::ValidMove* validMove );
						~ValidMoveNode();

						void compute( Othello::Board::Pun::Colors color, unsigned char depth );
						void prepareBottomStage( Othello::Board::Pun::Colors color );
						const Othello::Board::GameBoard* getBoard() const;
						const std::list<ValidMoveNode>& getNextNodes() const;
						ValidMove* getValidMove() const;
				};
			}
		}
	}

#endif
