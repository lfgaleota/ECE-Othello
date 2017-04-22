#ifndef _ECE_OTHELLO_UI_GAME_HPP_
	#define _ECE_OTHELLO_UI_GAME_HPP_

	#include "../../board/gameboard.hpp"
	#include "../../players/player.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace UI
		namespace UI {
		    /// \class Game gameui.hpp
			class Game {
				protected:
					const Othello::Board::GameBoard::punArray m_board;
					const std::vector<Othello::Players::Player*>& m_players;
					const std::vector<Othello::Players::Player*>::iterator& m_currentPlayer;
					Othello::Board::Tree::ValidMoveNode* m_tree = nullptr;

				public:
					/// \fn GameOverloadConstructor
					/// \param {board, players, currentPlayer}
					Game( const Othello::Board::GameBoard::punArray board, const std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& currentPlayer ) : m_board( board ), m_players( players ), m_currentPlayer( currentPlayer ) {};
					/// \fn GameDestructor
					/// \param {no parameters}
					virtual ~Game() {};
					/// \fn showError
					/// \param {msg}
					virtual void showError( std::string msg ) = 0;
					/// \fn inform
					/// \param {msg}
					virtual void inform( std::string msg ) = 0;
					/// \fn informNoAvailableMoves
					/// \param {player}
					virtual void informNoAvailableMoves( Othello::Players::Player& player ) = 0;
					/// \fn getMove
					/// \param {no parameters}
					virtual Othello::Board::Move getMove() = 0;
					/// \fn playerTurnBegin
					/// \param {player}
					virtual void playerTurnBegin( Othello::Players::Player& player ) = 0;
					/// \fn playerTurnEnd
					/// \param {player}
					virtual void playerTurnEnd( Othello::Players::Player& player ) = 0;
					/// \fn victory
					/// \param {player}
					virtual void victory( Othello::Players::Player* player ) = 0;
					/// \fn setTree
					/// \param {head}
					void setTree( Othello::Board::Tree::ValidMoveNode* head ) {
						m_tree = head;
					}
			};
		}
	}

#endif
