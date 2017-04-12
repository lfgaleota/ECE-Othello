#ifndef _ECE_SIAM_UI_GAME_HPP_
	#define _ECE_SIAM_UI_GAME_HPP_

	#include "../board.hpp"
	#include "../player.hpp"

	namespace Othello {
		namespace UI {
			class Game {
				protected:
					const std::vector<std::vector<Pun>>& m_board;
					const std::vector<Player>& m_players;
					const std::vector<Player>::iterator& m_currentPlayer;

				public:
					Game( const std::vector<std::vector<Pun>>& board, const std::vector<Player>& players, std::vector<Player>::iterator& currentPlayer ) : m_board( board ), m_players( players ), m_currentPlayer( currentPlayer ) {};
					virtual ~Game() {};
					virtual void showError( std::string msg ) = 0;
					virtual void getPlayerCoords( unsigned int& x, unsigned int& y, Siam::Matrixs::Direction* dir )= 0;
					virtual void addPiece( const Object*, unsigned int x, unsigned int y ) = 0;
					virtual void playerTurnBegin( Player& player ) = 0;
					virtual void playerTurnEnd( Player& player ) = 0;
					virtual void victory( Player& player ) = 0;
			};
		}
	}



#endif
