#ifndef ECE_OTHELLO_DIRECTIONVECTOR_HPP
#define ECE_OTHELLO_DIRECTIONVECTOR_HPP

#include <list>

struct DirectionVector {
	const char x;
	const char y;

	DirectionVector( char direction_x, char direction_y );

	const static std::list<DirectionVector> directions;
};

bool const operator==( DirectionVector& lhs, DirectionVector& rhs );

#endif //ECE_OTHELLO_DIRECTIONVECTOR_HPP
