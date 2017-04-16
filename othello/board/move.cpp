#include "../inc/board/move.hpp"

using namespace Othello::Board;

Move::Move( unsigned char x, unsigned char y ) : x ( x ), y( y ), color( Pun::blank ) {}

Move::Move( unsigned char x, unsigned char y, Pun::Colors color ) : x ( x ), y( y ), color( color ) {}

Move::Move( const Move &move ) : x( move.x ), y( move.y ), color( move.color ) {}

bool operator==( const Move& lhs, const Move& rhs ) {
	return ( lhs.x == rhs.x && lhs.y == rhs.y );
}

bool operator<( const Move& lhs, const Move& rhs ) {
	return ( lhs.x < rhs.x && lhs.y < rhs.y );
}