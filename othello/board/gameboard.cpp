#include "../inc/board/gameboard.hpp"

using namespace std;
using namespace Othello::Board;

GameBoard::GameBoard() { // : m_board( 8, vector<Pun>( 8 ) )
	for( unsigned char i = 0; i < GameBoard::sizeEdge; i++ ) {
		for( unsigned char j = 0; j < GameBoard::sizeEdge; j++ ) {
			if(( i == 3 && j == 3 ) || ( i == 4 && j == 4 )) {
				quickSet( i, j, Pun::black );
			} else {
				if(( i == 3 && j == 4 ) || ( i == 4 && j == 3 )) {
					quickSet( i, j, Pun::white );
				} else {
					quickSet( i, j, Pun::blank );
				}
			}
		}
	}

	//toutes les cases ayant un voisin à l'initialisation

	quickEmptyNeighborsSet( 2, 2 );
	quickEmptyNeighborsSet( 2, 3 );
	quickEmptyNeighborsSet( 2, 4 );
	quickEmptyNeighborsSet( 2, 5 );
	quickEmptyNeighborsSet( 3, 2 );
	quickEmptyNeighborsSet( 4, 2 );
	quickEmptyNeighborsSet( 5, 2 );
	quickEmptyNeighborsSet( 5, 3 );
	quickEmptyNeighborsSet( 5, 4 );
	quickEmptyNeighborsSet( 5, 5 );
	quickEmptyNeighborsSet( 4, 5 );
	quickEmptyNeighborsSet( 3, 5 );
}

GameBoard::GameBoard( GameBoard& ref ) {
	m_emptyNeighbors = ref.m_emptyNeighbors;
	std::memcpy( m_board, ref.m_board, sizeof( Pun ) * GameBoard::size );
}

GameBoard::~GameBoard() {

}

const GameBoard::punArray GameBoard::getBoard() {
	return (const GameBoard::punArray) m_board;
}

const std::list<ValidMove> &GameBoard::getValidMoves() {
	return m_validMoves;
}

const Pun::Colors GameBoard::at( const unsigned char x, const unsigned char y ) {
	if( x < GameBoard::sizeEdge && y < GameBoard::sizeEdge )
		return quickAt( x, y );
	else
		throw std::out_of_range( "Accessing outside of m_board range." );
}

const Pun::Colors GameBoard::quickAt( const unsigned char x, const unsigned char y ) {
	return m_board[ x ][ y ];
}

void GameBoard::set( const unsigned char x, const unsigned char y, const Pun::Colors color ) {
	if( x < GameBoard::sizeEdge && y < GameBoard::sizeEdge )
		return quickSet( x, y, color );
	else
		throw std::out_of_range( "Accessing outside of m_board range." );
}

void GameBoard::quickSet( const unsigned char x, const unsigned char y, const Pun::Colors color ) {
	m_board[ x ][ y ] = color;
}

uint64_t GameBoard::quickEmptyNeighborsGet( const unsigned char index ) {
	return m_emptyNeighbors & ( ( (uint64_t) 1 ) << index );
}

void GameBoard::emptyNeighborsSet( const unsigned char x, const unsigned char y ) {
	if( x < GameBoard::sizeEdge && y < GameBoard::sizeEdge ) {
		quickEmptyNeighborsSet( x, y );
	} else {
		throw std::out_of_range( "Accessing outside of empty neighbors range." );
	}
}

void GameBoard::quickEmptyNeighborsSet( const unsigned char x, const unsigned char y ) {
	m_emptyNeighbors |= ( ( (uint64_t) 1 ) << ( x * 8 + y ) );
}

void GameBoard::emptyNeighborsUnset( const unsigned char x, const unsigned char y ) {
	if( x < GameBoard::sizeEdge && y < GameBoard::sizeEdge ) {
		quickEmptyNeighborsUnset( x, y );
	} else {
		throw std::out_of_range( "Accessing outside of empty neighbors range." );
	}
}

void GameBoard::quickEmptyNeighborsUnset( const unsigned char x, const unsigned char y ) {
	m_emptyNeighbors &= ~( ( (uint64_t) 1 ) << ( x * 8 + y ) );
}

void GameBoard::computeValidMoves( Pun::Colors color ) {
	uint64_t value;
	m_validMoves.clear();

	// On parcours la liste des voisins vides, qui contient la liste de tous les emplacements vides voisins d'un pion
	for( unsigned char i = 0; i < GameBoard::size; i++ ) {
		value = quickEmptyNeighborsGet( i );
		if( value ) {
			Move emptyNeighbor( (unsigned char) ( i / 8 ), (unsigned char) ( i % 8 ), color );
			// On teste si un pion de la couleur demandé existe dans toutes les directions (à optimiser ?)
			ValidMove validMove = ValidMove( emptyNeighbor );
			for( const DirectionVector &dvec : DirectionVector::directions ) {
				if( isValidDirection( emptyNeighbor, dvec, color ) )
					// Si la direction comporte un pion de la couleur demandée, alors elle est valide et on l'ajoute
					validMove.addDirection( dvec );
			}
			// Si on a au moins une direction correct, on a un mouvement valide, on l'ajoute
			if( validMove.directions.size() > 0 )
				m_validMoves.push_back( validMove );
		}
	}
}

bool GameBoard::isValidDirection( Move position, DirectionVector dvec, Pun::Colors color ) {
	try {
		unsigned char x = position.x, y = position.y;
		Pun::Colors opposite = Pun::opposite( color );
		x += dvec.x;
		y += dvec.y;
		Pun::Colors next = at( x, y );
		if( next != opposite )
			return false;
		do {
			x += dvec.x;
			y += dvec.y;
			next = at( x, y );
		} while( next == opposite );
		if( next == color )
			return true;
	} catch( std::out_of_range e ) {
		// On est en dehors du plateau, on n'a donc pas trouvé de pion de la couleur demandé sur la direction demandée
	}
	return false;
}

void GameBoard::play( Move move ) {
	for( ValidMove &validMove: m_validMoves ) {
		if( move == validMove ) {
			// On insert la nouvelle pièce
			quickSet( move.x, move.y, move.color );
			// On retourne toutes les pièces dans les directions concernées
			for( DirectionVector& direction : validMove.directions ) {
				turnOverPuns( move, direction );
			}
			// On supprime la position actuelle des emplacements vides et on rajoute ses voisins vides
			quickEmptyNeighborsUnset( move.x, move.y );
			addEmptyNeighbors( move );
			return;
		}
	}

	// Mauvais coup
	throw exceptions::invalid_move( "Not a valid move." );
}

void GameBoard::turnOverPuns( Move position, DirectionVector dvec ) {
	try {
		for( unsigned char x = position.x + dvec.x, y = position.y + dvec.y; at( x, y ) != position.color; x += dvec.x, y += dvec.y )
			quickSet( x, y, position.color );
	} catch( std::out_of_range e ) {
		// On est en dehors du plateau, gros problème ! Cela ne devrait pas être le cas si le coup est valide.
	}
}

void GameBoard::addEmptyNeighbors( Move position ) {
	addEmptyNeighbors( position.x, position.y );
}

void GameBoard::addEmptyNeighbors( unsigned char posx, unsigned char posy ) {
	for( unsigned char x = (unsigned char) ( posx - 1 ); x <= posx + 1; x++ ) {
		for( unsigned char y = (unsigned char) ( posy - 1 ); y <= posy + 1; y++ ) {
			try {
				if( at( x, y ) == Pun::blank )
					quickEmptyNeighborsSet( (unsigned char) x, (unsigned char) y );
			} catch( std::out_of_range e ) {
				// On est en dehors du plateau, rien de grave, ça peut arriver.
			}
		}
	}
}
