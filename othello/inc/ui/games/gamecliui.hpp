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
						/// \param {no parameters}
						void display();
						/// \fn displayMatrix
						/// \param {no parameters}
						void displayMatrix();
						/// \fn displayPlayers
						/// \param {no parameters}
						void displayPlayers();
						/// \fn displayCounts
						/// \param {no parameters}
						void displayCounts();
						/// \fn displayCount
						/// \param {color}
						void displayCount( Othello::Board::Pun::Colors color );
						/// \fn loadDisplayerMatrix
						/// \param {no parameters}
						void loadDisplayMatrix();
						/// \fn showPiece
						/// \param {color, offsetX, offsetY}
						void showPiece( Othello::Board::Pun::Colors color, unsigned int offsetX, unsigned int offsetY );
						/// \fn higlightSelectedPiece
						/// \param {x, y, color}
						void highlightSelectedPiece( unsigned char x, unsigned char y, unsigned char color );
						/// \fn pauseMenu
						/// \param {no parameters}
						void pauseMenu();

					public:
						/// \fn CLIOverloadConstructor
						/// \param {oboard, board, players, currentPlayer}
						CLI( Othello::Board::GameBoard& oboard, const Othello::Board::GameBoard::punArray board, const std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& currentPlayer );
						/// \fn CLIDestructor
						/// \param {no parameters}
						~CLI();
						/// \fn showError
						/// \param {msg}
						void showError( std::string msg );
						/// \fn informNoAvailableMoves
						/// \param {player}
						void informNoAvailableMoves( Othello::Players::Player& player );
						/// \fn inform
						/// \param {msg}
						void inform( std::string msg );
						/// \fn getMove
						/// \param {no parameters}
						Othello::Board::Move getMove();
						/// \fn playerTurnBegin
						/// \param {player}
						void playerTurnBegin( Othello::Players::Player& player );
						/// \fn playerTurnEnd
						/// \param {player}
						void playerTurnEnd( Othello::Players::Player& player );
						/// \fn victory
						/// \param {player}
						void victory( Othello::Players::Player* player );
				};
			}
		}
	}

#endif
