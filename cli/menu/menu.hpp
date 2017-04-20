#ifndef _FUNCTIONS_CLI_MENU_HPP_
	#define _FUNCTIONS_CLI_MENU_HPP_

	#include <iostream>
	#include <vector>
	#include "../cli.hpp"

	namespace Functions {
	    /// \namespace CLIs
		namespace CLIs {
		    /// \class menu menu.hpp
			class Menu {
				private:
					std::string m_header;
					std::vector<std::string> m_choices;
					unsigned int m_choice = 1;

				public:
					/// \fn Menu
					Menu( std::string header, std::vector<std::string> choices, unsigned char back_color, unsigned char header_color, unsigned char selection_color, unsigned int minimal_height = 0, void ( *intermediateDisplay )() = nullptr );
					/// \fn setOffsets
					void setOffsets( unsigned int& offset_x, unsigned int& offset_y );
					/// \fn getChoice
					unsigned int getChoice() const;
			};
		}
	}
#endif
