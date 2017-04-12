#ifndef _ECE_OTHELLO_UI_GAMES_CLI_HPP_
	#define _ECE_OTHELLO_UI_GAMES_CLI_HPP_

	//#define SIMPLE_UI true

	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include "../../board.hpp"
	#include "../../player.hpp"
	#include "gameui.hpp"
	#include "../../../cli/cli.hpp"

	namespace Othello {
		namespace UI {
			namespace Games {
				class CLI : public Othello::UI::Game {
					private:
						Functions::CLI cli;
						std::vector<std::string> m_displayMatrix;
						Board& m_oboard;

						void display();
						void displayMatrix();
						void displayPlayers();
						void loadDisplayMatrix();
						void showPiece( Pun::Colors color, unsigned int offsetX, unsigned int offsetY );
						void highlightSelectedPiece( unsigned char x, unsigned char y, unsigned char color );

					public:
						CLI( Board& oboard, const Board::punArray board, const std::vector<Player*>& players, std::vector<Player*>::iterator& currentPlayer );
						~CLI();
						void showError( std::string msg );
						Move getMove();
						void playerTurnBegin( Player& player );
						void playerTurnEnd( Player& player );
						void victory( Player& player );
				};
			}
		}
	}

#endif
