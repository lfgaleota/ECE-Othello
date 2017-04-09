#ifndef ECE_OTHELLO_VALIDMOVE_HPP
#define ECE_OTHELLO_VALIDMOVE_HPP

#include <list>
#include "move.hpp"
#include "direction_vector.hpp"

struct ValidMove : public Move {
	std::list<DirectionVector> directions;

	ValidMove( unsigned char x, unsigned char y );
	inline void addDirection( DirectionVector dvec );
	inline void addDirection( char x, char y );
};

#endif //ECE_OTHELLO_VALIDMOVE_HPP
