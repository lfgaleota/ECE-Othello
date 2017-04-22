#include "../inc/board/valid_move.hpp"

using namespace Othello::Board;

/**
* @brief Constructeur surchargé de la structure ValidMove
**/
ValidMove::ValidMove( unsigned char x, unsigned char y ) : Move( x, y ) {}

/**
* @brief Constructeur surchargé de la structure ValidMove
**/
ValidMove::ValidMove( const Move &move ) : Move( move ) {}
