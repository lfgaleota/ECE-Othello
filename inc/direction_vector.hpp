#ifndef ECE_OTHELLO_DIRECTIONVECTOR_HPP
#define ECE_OTHELLO_DIRECTIONVECTOR_HPP


struct DirectionVector {
	const char x;
	const char y;

	DirectionVector( char direction_x, char direction_y );
};

bool const operator==( DirectionVector& lhs, DirectionVector& rhs ) {
	return ( lhs.x == rhs.x && lhs.y == rhs.y );
}

#endif //ECE_OTHELLO_DIRECTIONVECTOR_HPP
