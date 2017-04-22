#ifndef _ECE_OTHELLO_BOARD_GAMEBOARDCONSTANTS_HPP_
	#define _ECE_OTHELLO_BOARD_GAMEBOARDCONSTANTS_HPP_

	#include "pun.hpp"

	namespace Othello {
		namespace Board {
			const static unsigned char sizeEdge = 8;
			const static unsigned char size = sizeEdge * sizeEdge;
			const static size_t sizeMemory = (size_t) ( size * 4 );

			typedef Pun::Colors (*punArray)[ sizeEdge ];
		}
	}
#endif
