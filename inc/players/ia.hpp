#ifndef _ECE_OTHELLO_ARTIFICIAL_HPP_
	#define _ECE_OTHELLO_ARTIFICIAL_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "player.hpp"

	namespace Othello {
		namespace Players {
			class IA : public Player {
				private:

					//dunno yet

				public:

					std::pair<int, int> ask_for_move();
			};
		}
	}

#endif
