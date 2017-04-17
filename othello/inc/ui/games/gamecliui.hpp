#ifndef _ECE_OTHELLO_UI_GAMES_CLI_HPP_
	#define _ECE_OTHELLO_UI_GAMES_CLI_HPP_

	//#define SIMPLE_UI true

	#include <iostream>
	#include <iomanip>
	#include <fstream>
	#include <sstream>
	#include "../../board/gameboard.hpp"
	#include "../../players/player.hpp"
	#include "gameui.hpp"
	#include "../../../../cli/cli.hpp"
	#include "../../../../cli/menu/menu.hpp"

	namespace Othello {
		namespace UI {
			namespace Games {
				class CLI : public Othello::UI::Game {
					private:
						Functions::CLI cli;
						std::vector<std::string> m_displayMatrix;
						Othello::Board::GameBoard& m_oboard;

						void display();
						void displayMatrix();
						void displayPlayers();
						void displayCounts();
						void displayCount( Othello::Board::Pun::Colors color );
						void loadDisplayMatrix();
						void showPiece( Othello::Board::Pun::Colors color, unsigned int offsetX, unsigned int offsetY );
						void highlightSelectedPiece( unsigned char x, unsigned char y, unsigned char color );
						void pauseMenu();

					public:
						CLI( Othello::Board::GameBoard& oboard, const Othello::Board::GameBoard::punArray board, const std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& currentPlayer );
						~CLI();
						void showError( std::string msg );
						void informNoAvailableMoves( Othello::Players::Player& player );
						void inform( std::string msg );
						Othello::Board::Move getMove();
						void playerTurnBegin( Othello::Players::Player& player );
						void playerTurnEnd( Othello::Players::Player& player );
						void victory( Othello::Players::Player* player );
				};
			}
		}
	}

#endif
