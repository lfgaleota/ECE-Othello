#include "../inc/board/direction_vector.hpp"

using namespace Othello::Board;

DirectionVector::DirectionVector( char direction_x, char direction_y ) : x( direction_x ), y( direction_y ) {}

bool const operator==( DirectionVector& lhs, DirectionVector& rhs ) {
	return ( lhs.x == rhs.x && lhs.y == rhs.y );
}
