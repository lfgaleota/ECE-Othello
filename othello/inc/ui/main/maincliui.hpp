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

	/// \namespace Othello
	namespace Othello {
        /// \namespace UI
		namespace UI {
		    /// \namespace Main
			namespace Main {
			    /// \class CLI
			    /// \brief classe d'interface permettant de charger et d'afficher le jeu
				class CLI {
					private:
						std::vector<Othello::Players::Player*> m_players;
						Functions::CLI m_cli;
						std::string m_logo;

                        /// \fn loadGame
                        /// \param {no Parameters}
						void loadGame();
						/// \fn newGame
                        /// \param {no Parameters}
						void newGame();
						/// \fn menu
                        /// \param {no Parameters}
						void menu();
						/// \fn newPVP
                        /// \param {no Parameters}
						void newPVP();
						/// \fn newPVAI
                        /// \param {no Parameters}
						void newPVAI();
					public:
					    /// \fn defaultConstructor
                        /// \param {no Parameters}
						CLI();

                        /// \fn logo
                        /// \param {no Parameters}
						static void logo();
				};
			}
		}
	}
#endif
