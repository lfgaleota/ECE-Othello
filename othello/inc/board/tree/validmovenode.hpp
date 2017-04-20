#ifndef _ECE_OTHELLO_BOARD_TREE_VALIDMOVENODE_HPP_
	#define _ECE_OTHELLO_BOARD_TREE_VALIDMOVENODE_HPP_

	#include <list>
	#include <vector>
	#include "../gameboard.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Board
		namespace Board {
		    /// \namespace Tree
			namespace Tree {
			    /// \class ValidMoveNode validmovenode.hpp
				class ValidMoveNode {
					friend class Othello::Algorithms::MiniMax;

					private:
						Othello::Board::GameBoard* m_board;
						Othello::Board::ValidMove* m_validMove;
						std::list<ValidMoveNode> m_nextNodes;

					public:
						/// \fn ValidMoveNodeOverloadConstructor
						ValidMoveNode( Othello::Board::GameBoard* board );
						/// \fn ValidMoveNodeOverloadConstructorBis
						ValidMoveNode( Othello::Board::GameBoard* board, Othello::Board::ValidMove* validMove );
						/// \fn ValidMoveNodeDestructor
						~ValidMoveNode();

						/// \fn compute
						void compute( Othello::Board::Pun::Colors color, unsigned char depth );
						/// \fn prepareBottomStage
						void prepareBottomStage( Othello::Board::Pun::Colors color );
						/// \fn getBoard
						const Othello::Board::GameBoard* getBoard() const;
						/// \fn getNextNodes
						const std::list<ValidMoveNode>& getNextNodes() const;
						/// \fn getValidMoveGetter
						ValidMove* getValidMove() const;
				};
			}
		}
	}

#endif
