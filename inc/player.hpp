#ifndef _ECE_OTHELLO_PLAYER_HPP_
	#define _ECE_OTHELLO_PLAYER_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include "pun.hpp"
	#include "move.hpp"


	class Player {
		protected:
			std::string m_name;
			Pun::Colors m_color;

		public:
			Player( std::string name, Pun::Colors color );

			const std::string &getName() const;
			Pun::Colors getColor() const;

			virtual Move getMove() = 0;
	};

#endif
