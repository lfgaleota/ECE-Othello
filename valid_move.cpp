#include "inc/valid_move.hpp"

ValidMove::ValidMove( unsigned char x, unsigned char y ) : Move( x, y ) {}

void ValidMove::addDirection( char x, char y ) {
	directions.push_back( DirectionVector( x, y ) );
}

void ValidMove::addDirection( DirectionVector dvec ) {
	directions.push_back( dvec );

}
