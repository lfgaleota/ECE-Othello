#include "../inc/board/move.hpp"

using namespace Othello::Board;

/**
* @brief Constructeur surchargé de la structure Move
**/
Move::Move( unsigned char x, unsigned char y ) : x ( x ), y( y ), color( Pun::blank ) {}

/**
* @brief Constructeur surchargé de la structure Move
**/
Move::Move( unsigned char x, unsigned char y, Pun::Colors color ) : x ( x ), y( y ), color( color ) {}

/**
* @brief Constructeur surchargé de la structure Move
**/
Move::Move( const Move &move ) : x( move.x ), y( move.y ), color( move.color ) {}

/**
* @brief Surcharge de l'opérateur ==
**/
bool operator==( const Move& lhs, const Move& rhs ) {
	return ( lhs.x == rhs.x && lhs.y == rhs.y );
}

/**
* @brief Surcharge de l'opérateur <
**/
bool operator<( const Move& lhs, const Move& rhs ) {
	return ( lhs.x < rhs.x && lhs.y < rhs.y );
}
