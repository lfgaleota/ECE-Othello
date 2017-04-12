#include "../../inc/board/direction_vector.hpp"

using namespace Othello::Board;

DirectionVector::DirectionVector( char direction_x, char direction_y ) : x( direction_x ), y( direction_y ) {}

const std::list<DirectionVector> DirectionVector::directions = std::list<DirectionVector>( { DirectionVector( -1, -1 ), DirectionVector( -1, 0 ), DirectionVector( 0, -1 ), DirectionVector( 0, 1 ), DirectionVector( 1, 0 ), DirectionVector( 1, 1 ), DirectionVector( -1, -1 ), DirectionVector( -1, 1 ), DirectionVector( 1, -1 ) } );

bool const operator==( DirectionVector& lhs, DirectionVector& rhs ) {
	return ( lhs.x == rhs.x && lhs.y == rhs.y );
}