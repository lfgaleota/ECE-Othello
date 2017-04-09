#include "inc/board.hpp"

Board::Board()
		: board( 8, vector<Pun>( 8 )) {
	for( unsigned int i = 0; i < board.size(); i++ ) {
		for( unsigned int j = 0; j < board[ i ].size(); j++ ) {
			if(( i == 3 && j == 3 ) || ( i == 4 && j == 4 )) {
				board[ i ][ j ] = black;
			} else {
				if(( i == 3 && j == 4 ) || ( i == 4 && j == 3 )) {
					board[ i ][ j ] = white;
				} else {
					board[ i ][ j ] = blank;
				}
			}
		}
	}

	//toutes les cases ayant un voisin � l'initialisation

	emptySlots.insert( make_pair( 2, 2 ));
	emptySlots.insert( make_pair( 2, 3 ));
	emptySlots.insert( make_pair( 2, 4 ));
	emptySlots.insert( make_pair( 2, 5 ));
	emptySlots.insert( make_pair( 3, 2 ));
	emptySlots.insert( make_pair( 4, 2 ));
	emptySlots.insert( make_pair( 5, 2 ));
	emptySlots.insert( make_pair( 5, 3 ));
	emptySlots.insert( make_pair( 5, 4 ));
	emptySlots.insert( make_pair( 5, 5 ));
	emptySlots.insert( make_pair( 4, 5 ));
	emptySlots.insert( make_pair( 3, 5 ));
}


Board::~Board() {

}

vector<vector<Pun>> Board::getBoard() {
	return board;
}

void Board::play( pair<int, int> _move, bool turn ) {
	if( turn )
		board[ _move.first ][ _move.second ] = black;
	else
		board[ _move.first ][ _move.second ] = white;

	//ICI on appelle le changement de couleur nananana
	//make_changes(_move);
}

void Board::find_empty_spots( pair<int, int> _move ) {
	for( unsigned int i = 0; i < 8; i++ ) {
		switch( i ) {

			case 0 :

				//en haut
				break;

			case 1 :

				//en bas
				break;

			case 2 :

				//a gauche
				break;

			case 3 :

				//� droite
				break;

			case 4 :

				//diago haut gauche
				break;


			case 5 :

				//diago haut droite
				break;

			case 6 :

				//diago bas gauche
				break;

			case 7 :

				//diago bas droite
				break;

			default :

				break;
		}
	}
}

bool Board::test_a_move( bool turn, pair<int, int> spot ) {
	for( unsigned int i = 0; i < 8; i++ ) {
		switch( i ) {

			case 0 :

				//en haut
				//if(possible) return true, else continue
				break;

			case 1 :

				//en bas
				break;

			case 2 :

				//a gauche
				break;

			case 3 :

				//� droite
				break;

			case 4 :

				//diago haut gauche
				break;


			case 5 :

				//diago haut droite
				break;

			case 6 :

				//diago bas gauche
				break;

			case 7 :

				//diago bas droite
				//if(possible) return true, else return false
				break;

			default :

				break;
		}
	}

}

void Board::find_possible_moves( bool turn ) {
	bool possibility = false;
	//il faut commencer par vider le vector des "anciens" coups possibles !
	validMoves.erase( validMoves.begin(), validMoves.end());

	for( auto elem : emptySlots ) {
		possibility = test_a_move( turn, elem );
		if( possibility ) {
			validMoves.push_back( elem );
		}
	}
}

void Board::make_changes( pair<int, int> _move ) {
	for( unsigned int i = 0; i < 8; i++ ) {
		switch( i ) {

			case 0 :

				//en haut
				break;

			case 1 :

				//en bas
				break;

			case 2 :

				//a gauche
				break;

			case 3 :

				//� droite
				break;

			case 4 :

				//diago haut gauche
				break;


			case 5 :

				//diago haut droite
				break;

			case 6 :

				//diago bas gauche
				break;

			case 7 :

				//diago bas droite
				break;

			default :

				break;
		}
	}

}

