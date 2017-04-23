#ifndef _ECE_OTHELLO_UI_MAIN_CLI_HPP_
	#define _ECE_OTHELLO_UI_MAIN_CLI_HPP_

	#include <iostream>
	#include <vector>
	#include <ios>
	#include <fstream>
	#include <sstream>
	#include "../../game.hpp"
	#include "../../../../cli/cli.hpp"
	#include "../../../../cli/menu/menu.hpp"
	#include "../../players/human.hpp"
	#include "../../players/randomai.hpp"
	#include "../../players/simpleai.hpp"
	#include "../../players/enhancedai.hpp"

	#define LOGO_WIDTH 37
	#define LOGO_HEIGHT 7

	namespace Othello {
		namespace UI {
			namespace Main {
				class CLI {
					private:
						std::vector<Othello::Players::Player*> m_players;
						Functions::CLI m_cli;
						std::string m_logo;

						void loadGame();
						void newGame();
						void menu();
						void newPVP();
						void newPVAI();
					public:
						CLI();

						static void logo();
				};
			}
		}
	}
#endif
