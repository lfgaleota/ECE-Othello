#include "../../inc/board/valid_move.hpp"

ValidMove::ValidMove( unsigned char x, unsigned char y ) : Move( x, y ) {}

ValidMove::ValidMove( const Move &move ) : Move( move ) {}
