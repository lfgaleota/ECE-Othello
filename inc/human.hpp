#ifndef HUMAN_HPP_INCLUDED
#define HUMAN_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
#include "ui/games/gameui.hpp"

class Human : public Player {
	private:
		Othello::UI::Game* m_ui;

	public:
		Human( std::string name, Pun::Colors color );

		Move getMove();

		void setUI( Othello::UI::Game *m_ui );
};


#endif // HUMAN_HPP_INCLUDED
