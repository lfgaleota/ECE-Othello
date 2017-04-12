#ifndef _ECE_OTHELLO_GAME_HPP_
	#define _ECE_OTHELLO_GAME_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "board.hpp"
	#include "player.hpp"
	#include "human.hpp"
	#include "ui/games/gameui.hpp"
	#include "ui/games/gamecliui.hpp"

	class Game {
		private:
			Board m_board; //game board
			std::vector<Player*>& m_players; //players
			std::vector<Player*>::iterator m_currentPlayer; //an iterator of players (we need to know who's turn it is)
			Othello::UI::Game* m_ui;
			bool won = false;

			void playerTurn();
			void victory();
			void preparePlayers();

		public:
			Game( std::vector<Player*>& players );
	};

#endif
