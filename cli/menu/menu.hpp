#ifndef _FUNCTIONS_CLI_MENU_HPP_
	#define _FUNCTIONS_CLI_MENU_HPP_

	#include <iostream>
	#include <vector>
	#include "../cli.hpp"

	namespace Functions {
		namespace CLIs {
			class Menu {
				private:
					std::string m_header;
					std::vector<std::string> m_choices;
					unsigned int m_choice = 0;

				public:
					Menu( std::string header, std::vector<std::string> choices, unsigned char back_color, unsigned char header_color, unsigned char selection_color, unsigned int minimal_height = 0, void ( *intermediateDisplay )() = nullptr );
					void setOffsets( unsigned int& offset_x, unsigned int& offset_y );
					unsigned int getChoice() const;
			};
		}
	}
#endif
