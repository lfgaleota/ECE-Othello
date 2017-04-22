#include "../inc/board/pun.hpp"

using namespace Othello::Board;

bool Pun::check( int v ) {
	if( v < static_cast<int>( Pun::Colors::blank ) ) return false;
	if( v > static_cast<int>( Pun::Colors::white ) ) return false;

	switch( static_cast<Pun::Colors>( v ) ) {
		case Pun::Colors::blank:
		case Pun::Colors::black:
		case Pun::Colors::white:
			return true;
		default:
			return false;
	}
}
