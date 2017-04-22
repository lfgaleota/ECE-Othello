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
						int m_eval = 0;

					public:
						/// \fn ValidMoveNodeOverloadConstructor
						/// \param {board}
						ValidMoveNode( Othello::Board::GameBoard* board );
						/// \fn ValidMoveNodeOverloadConstructorBis
						/// \param {board, validMove}
						ValidMoveNode( Othello::Board::GameBoard* board, Othello::Board::ValidMove* validMove );
						/// \fn ValidMoveNodeDestructor
						/// \param {no parameters}
						~ValidMoveNode();

						/// \fn compute
						/// \param {color, depth}
						void compute( Othello::Board::Pun::Colors color, unsigned char depth );
						/// \fn prepareBottomStage
						/// \param {color}
						void prepareBottomStage( Othello::Board::Pun::Colors color );
						/// \fn getBoard
						/// \param {no parameters}
						const Othello::Board::GameBoard* getBoard() const;
						/// \fn getNextNodes
						/// \param {no parameters}
						const std::list<ValidMoveNode>& getNextNodes() const;
						/// \fn getValidMoveGetter
						/// \param {no parameters}
						ValidMove* getValidMove() const;

						int getEval() const;
				};
			}
		}
	}

#endif
