#ifndef _ECE_OTHELLO_UI_GAME_HPP_
	#define _ECE_OTHELLO_UI_GAME_HPP_

	#include "../../board/gameboard.hpp"
	#include "../../players/player.hpp"

	namespace Othello {
		namespace UI {
			class Game {
				protected:
					const Othello::Board::GameBoard::punArray m_board;
					const std::vector<Othello::Players::Player*>& m_players;
					const std::vector<Othello::Players::Player*>::iterator& m_currentPlayer;

				public:
					Game( const Othello::Board::GameBoard::punArray board, const std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& currentPlayer ) : m_board( board ), m_players( players ), m_currentPlayer( currentPlayer ) {};
					virtual ~Game() {};
					virtual void showError( std::string msg ) = 0;
					virtual void inform( std::string msg ) = 0;
					virtual void informNoAvailableMoves( Othello::Players::Player& player ) = 0;
					virtual Othello::Board::Move getMove() = 0;
					virtual void playerTurnBegin( Othello::Players::Player& player ) = 0;
					virtual void playerTurnEnd( Othello::Players::Player& player ) = 0;
					virtual void victory( Othello::Players::Player* player ) = 0;
			};
		}
	}

#endif
