#ifndef ECE_OTHELLO_VALIDMOVE_HPP
#define ECE_OTHELLO_VALIDMOVE_HPP

#include <list>
#include "move.hpp"
#include "direction_vector.hpp"

struct ValidMove : public Move {
	std::list<DirectionVector> directions;

	ValidMove( unsigned char x, unsigned char y );
	ValidMove( const Move& move );

	inline void addDirection( DirectionVector dvec ) {
		directions.push_back( dvec );
	}
};

#endif //ECE_OTHELLO_VALIDMOVE_HPP
