#ifndef _ECE_OTHELLO_GAME_HPP_
	#define _ECE_OTHELLO_GAME_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "board/gameboard.hpp"
	#include "players/player.hpp"
	#include "players/human.hpp"
	#include "ui/games/gameui.hpp"
	#include "ui/games/gamecliui.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \class Game game.hpp
		class Game {
			private:
				Othello::Board::GameBoard m_board; //game board
				std::vector<Othello::Players::Player*>& m_players; //players
				std::vector<Othello::Players::Player*>::iterator m_currentPlayer; //an iterator of players (we need to know who's turn it is)
				Othello::UI::Game* m_ui;
				bool won = false;

				/// \fn playerTurn
				/// \param {no parameters}
				void playerTurn();
				/// \fn victory
				/// \param {no parameters}
				void victory();
				/// \fn verifyVictory
				/// \param {no parameters}
				void verifyVictory();
				/// \fn preparePlayers
				/// \param {no parameters}
				void preparePlayers();

			public:
				/// \fn GameOverloadConstructor
				/// \param {players}
				Game( std::vector<Othello::Players::Player*>& players );
		};
	}

#endif
