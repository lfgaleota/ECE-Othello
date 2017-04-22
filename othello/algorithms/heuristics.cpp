#include "../inc/algorithms/heuristics.hpp"

using namespace std;
using namespace Othello::Algorithms;
using namespace Othello::Board;

const int Heuristics::weightTable[ Othello::Board::sizeEdge ][ Othello::Board::sizeEdge ] = {
	{ 100, -50, 11, 8, 8, 11, -50, 100 },
	{ -50, -70, -4, 1, 1, -4, -70, -50 },
	{ 11, -4, 2, 2, 2, 2, -4, 11 },
	{ 8, 1, 2, -3, -3, 2, 1, 8 },
	{ 8, 1, 2, -3, -3, 2, 1, 8 },
	{ 11, -4, 2, 2, 2, 2, -4, 11 },
	{ -50, -70, -4, 1, 1, -4, -70, -50 },
	{ 100, -50, 11, 8, 8, 11, -50, 100 }
};

int Heuristics::simple( Othello::Board::GameBoard* ref, Othello::Board::Pun::Colors color ) {
	if( color == Pun::black )
		return ref->m_count.black - ref->m_count.white;
	else if( color == Pun::white )
		return ref->m_count.white - ref->m_count.black;
	return 0;
}

int Heuristics::normale( GameBoard* ref, Pun::Colors color, Pun::Colors opposite ) {
	int count, oppositeCount, emptyNeighbors = 0;
	float coinParity = 0, mobility = 0, weightedOccupancy = 0;
	Pun::Colors piece;

	/*
	 * Calcul de l'occupation
	 */
	for( unsigned char i = 0; i < Board::sizeEdge; i++ ) {
		for( unsigned char j = 0; j < Board::sizeEdge; j++ ) {
			piece = ref->quickAt( i, j );
			if( piece == color ) {
				weightedOccupancy += weightTable[ i ][ j ];
			} else if( piece == opposite ) {
				weightedOccupancy -= weightTable[ i ][ j ];
			}
		}
	}

	/*
	 * Calcul de la parité des pièces
	 */
	if( color == Pun::black ) {
		count = ref->m_count.black;
		oppositeCount = ref->m_count.white;
	} else {
		count = ref->m_count.white;
		oppositeCount = ref->m_count.black;
	}
	if( count > oppositeCount )
		coinParity = ( 100.0f * count ) / ( count + oppositeCount );
	else if( count < oppositeCount )
		coinParity = -( 100.0f * oppositeCount ) / ( count + oppositeCount );

	/*
	 * Calcul de la mobilité
	 */
	count = ref->m_validMoves.size();
	for( unsigned char i = 0; i < Board::size; i++ ) {
		if( ref->quickEmptyNeighborsGet( i ) )
			emptyNeighbors++;
	}
	// Pour accélérer un peu les calculs, on suppose directement que tous les autres voisins vides qui ne correspondent pas à un coup valide pour notre couleur correspondent à un coup valide pour le jouer adverse.
	oppositeCount = emptyNeighbors - count;
	if( count > oppositeCount )
		mobility = ( 100.0f * count ) / ( count + oppositeCount );
	else if( count < oppositeCount )
		mobility = -( 100.0f * oppositeCount ) / ( count + oppositeCount );

	/*
	 * Calcul de la valeur d'heuristique finale
	 */
	return ( int ) ( ( 10 * coinParity ) + ( 78.922f * mobility ) + ( 10 * weightedOccupancy ) );
}
