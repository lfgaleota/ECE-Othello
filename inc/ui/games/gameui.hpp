#ifndef _ECE_OTHELLO_UI_GAME_HPP_
	#define _ECE_OTHELLO_UI_GAME_HPP_

	#include "../../board/board.hpp"
	#include "../../players/player.hpp"

	namespace Othello {
		namespace UI {
			class Game {
				protected:
					const Board::punArray m_board;
					const std::vector<Player*>& m_players;
					const std::vector<Player*>::iterator& m_currentPlayer;

				public:
					Game( const Board::punArray board, const std::vector<Player*>& players, std::vector<Player*>::iterator& currentPlayer ) : m_board( board ), m_players( players ), m_currentPlayer( currentPlayer ) {};
					virtual ~Game() {};
					virtual void showError( std::string msg ) = 0;
					virtual Move getMove() = 0;
					virtual void playerTurnBegin( Player& player ) = 0;
					virtual void playerTurnEnd( Player& player ) = 0;
					virtual void victory( Player& player ) = 0;
			};
		}
	}

#endif
