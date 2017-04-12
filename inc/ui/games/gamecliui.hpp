#ifndef _ECE_SIAM_UI_GAMES_CLI_HPP_
	#define _ECE_SIAM_UI_GAMES_CLI_HPP_

	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include "../../matrix.hpp"
	#include "../../object.hpp"
	#include "../../objects/types/type.hpp"
	#include "../../player.hpp"
	#include "../gameui.hpp"
	#include "../../../../cli/cli.hpp"

	namespace Siam {
		namespace UI {
			namespace Games {
				class CLI : public Siam::UI::Game {
					private:

						void display();
						void displayMatrix();
						void displayPlayers();
						void displayActions();
						std::vector<std::string> m_displayMatrix;
						void loadDisplayMatrix();
						void showPiece( Object* elem );
						void highlightSelectedPiece( unsigned int x, unsigned int y, unsigned char color = BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );

					public:
						CLI( const std::vector<std::vector<Siam::Object*>>& board, const std::vector<Siam::Player>& players, std::vector<Siam::Player>::iterator& currentPlayer, Siam::UI::Audio::FMOD& fmod );
						~CLI();
						void showError( std::string msg );
						void getPlayerCoords( unsigned int& x, unsigned int& y, Siam::Matrixs::Direction* dir );
						void addPiece( const Object*, unsigned int x, unsigned int y );
						void removePiece( const Object* obj );
						void movePiece( std::map<const Siam::Object*, std::pair<unsigned int, unsigned int>>& movements );
						void orientPiece( const Object* obj );
						void ejectPiece( const Object* obj );
						void playerTurnBegin( Siam::Player& player );
						void playerTurnEnd( Siam::Player& player );
						Players::Action getPlayerAction( Siam::Player& player );
						void victory( Siam::Player& player );
						Functions::CLI cli;
				};
			}
		}
	}
#endif
