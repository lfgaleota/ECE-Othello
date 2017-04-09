#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "pun.hpp"

class Board {
	private:
		std::vector<std::vector<Pun>> board; //plateau de jeu
		std::set<std::pair<int, int>> emptySlots;
		std::vector<std::pair<int, int>> validMoves;


	public:
		Board();

		~Board();

		std::vector<std::vector<Pun>> getBoard();

		void find_empty_spots( std::pair<int, int> _move ); //fonction de recherche des cases vides ayant un voisin.
		bool test_a_move( bool turn, std::pair<int, int> spot );

		void find_possible_moves( bool turn );

		void play( std::pair<int, int> move );
};


#endif // BOARD_HPP_INCLUDED
