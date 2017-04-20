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

				public:
					/// \fn GameOverloadConstructor
					Game( const Othello::Board::GameBoard::punArray board, const std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& currentPlayer ) : m_board( board ), m_players( players ), m_currentPlayer( currentPlayer ) {};
					/// \fn GameDestructor
					virtual ~Game() {};
					/// \fn showError
					virtual void showError( std::string msg ) = 0;
					/// \fn inform
					virtual void inform( std::string msg ) = 0;
					/// \fn informNoAvailableMoves
					virtual void informNoAvailableMoves( Othello::Players::Player& player ) = 0;
					/// \fn getMove
					virtual Othello::Board::Move getMove() = 0;
					/// \fn playerTurnBegin
					virtual void playerTurnBegin( Othello::Players::Player& player ) = 0;
					/// \fn playerTurnEnd
					virtual void playerTurnEnd( Othello::Players::Player& player ) = 0;
					/// \fn victory
					virtual void victory( Othello::Players::Player* player ) = 0;
			};
		}
	}

#endif
