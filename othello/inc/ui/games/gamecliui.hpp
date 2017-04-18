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

	/// \namespace Othello
	namespace Othello {
	    /// \namespace UI
		namespace UI {
		    /// \namespace Games
			namespace Games {
			    /// \class CLI gamecliui.hpp
				class CLI : public Othello::UI::Game {
					private:
						Functions::CLI cli;
						std::vector<std::string> m_displayMatrix;
						Othello::Board::GameBoard& m_oboard;

						/// \fn display
						void display();
						/// \fn displayMatrix
						void displayMatrix();
						/// \fn displayPlayers
						void displayPlayers();
						/// \fn displayCounts
						void displayCounts();
						/// \fn displayCount
						void displayCount( Othello::Board::Pun::Colors color );
						/// \fn loadDisplayerMatrix
						void loadDisplayMatrix();
						/// \fn showPiece
						void showPiece( Othello::Board::Pun::Colors color, unsigned int offsetX, unsigned int offsetY );
						/// \fn higlightSelectedPiece
						void highlightSelectedPiece( unsigned char x, unsigned char y, unsigned char color );
						/// \fn pauseMenu
						void pauseMenu();

					public:
						/// \fn CLIOverloadConstructor
						CLI( Othello::Board::GameBoard& oboard, const Othello::Board::GameBoard::punArray board, const std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& currentPlayer );
						/// \fn CLIDestructor
						~CLI();
						/// \fn showError
						void showError( std::string msg );
						/// \fn informNoAvailableMoves
						void informNoAvailableMoves( Othello::Players::Player& player );
						/// \fn inform
						void inform( std::string msg );
						/// \fn getMove
						Othello::Board::Move getMove();
						/// \fn playerTurnBegin
						void playerTurnBegin( Othello::Players::Player& player );
						/// \fn playerTurnEnd
						void playerTurnEnd( Othello::Players::Player& player );
						/// \fn victory
						void victory( Othello::Players::Player* player );
				};
			}
		}
	}

#endif
