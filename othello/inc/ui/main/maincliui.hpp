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
	#include "../../winres.h"

	#define LOGO_WIDTH 37
	#define LOGO_HEIGHT 7

	/**
	* @namespace Othello
	* @details Espace de nommage du jeu.
	*/
	namespace Othello {
		/**
		 * @namespace UI
		 * @details Espace de nommage des interfaces du jeu.
		 */
		namespace UI {
			/**
			 * @namespace Main
			 * @details Espace de nommage des interfaces du menu.
			 */
			namespace Main {
				/**
				  * @class Allegro
				  * @brief Interface du menu console
				  */
				class CLI {
					private:
						std::vector<Othello::Players::Player*> m_players;
						Functions::CLI m_cli;
						std::string m_logo;
						Othello::UI::Audio::FMOD& m_fmod;

						/**
						* @brief Continueur de partie
						*/
						void loadGame();

						/**
						 * @brief Initiateur de partie
						 */
						void newGame();

						/**
						 * @brief Boucle de menu
						 */
						void menu();

						/**
						 * @brief Initiateur de partie PVP
						 */
						void newPVP();

						/**
						 * @brief Initiateur de partie PVAI
						 */
						void newPVAI();

					public:
						/**
						 * @brief Constructeur
						 * @param fmod Référence vers un objet de gestion #FMOD
						 */
						CLI( Othello::UI::Audio::FMOD& fmod );

						/**
						 * @brief Afficheur de logo
						 * @details Appelée par le menu pour afficher le logo
						 */
						static void logo();
				};
			}
		}
	}
#endif
