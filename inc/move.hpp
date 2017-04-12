#ifndef ECE_OTHELLO_MOVE_HPP
#define ECE_OTHELLO_MOVE_HPP


#include "pun.hpp"

struct Move {
	const unsigned char x;
	const unsigned char y;
	const Pun::Colors color;

	Move( unsigned char x, unsigned char y );
	Move( unsigned char x, unsigned char y, Pun::Colors color );
	Move( const Move& move );
};

bool operator==( const Move& lhs, const Move& rhs );

bool operator<( const Move& lhs, const Move& rhs );

#endif //ECE_OTHELLO_MOVE_HPP