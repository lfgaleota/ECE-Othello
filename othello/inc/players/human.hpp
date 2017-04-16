#ifndef _ECE_OTHELLO_PLAYERS_HUMAN_HPP_
	#define _ECE_OTHELLO_PLAYERS_HUMAN_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "player.hpp"
	#include "../ui/games/gameui.hpp"

	namespace Othello {
		namespace Players {
			class Human : public Player {
				private:
					Othello::UI::Game* m_ui;

				public:
					Human( std::string name, Othello::Board::Pun::Colors color );

					Othello::Board::Move getMove();

					void setUI( Othello::UI::Game *m_ui );
			};
		}
	}

#endif
