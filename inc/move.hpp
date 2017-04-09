#ifndef ECE_OTHELLO_MOVE_HPP
#define ECE_OTHELLO_MOVE_HPP


struct Move {
	const unsigned char x;
	const unsigned char y;

	Move( unsigned char x, unsigned char y );
};

bool const operator==( Move& lhs, Move& rhs ) {
	return ( lhs.x == rhs.x && lhs.y == rhs.y );
}

#endif //ECE_OTHELLO_MOVE_HPP
