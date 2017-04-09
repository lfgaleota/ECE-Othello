#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "othello.hpp"

class Board {
	private :
		std::vector<std::vector<Pun>> m_game_board; //plateau de jeu
		std::pair<int, int> _move; //euuuh ca on va voir si on le met vraiment là, pas sur
		std::set<std::pair<int, int>> m_empty_spots;
		std::vector<std::pair<int, int>> m_possible_moves;


	public :

		Board();

		~Board();

		std::vector<std::vector<Pun>> getBoard();

		void find_empty_spots( std::pair<int, int> _move ); //fonction de recherche des cases vides ayant un voisin.
		bool test_a_move( bool turn, std::pair<int, int> spot );

		void find_possible_moves( bool turn );

		void play( std::pair<int, int> _move,
				   bool turn ); //reçoit des coordonnées et ajoute un pion du joueur correspondant à l'endroit voulu ?
		void make_changes( std::pair<int, int> _move );
};


#endif // BOARD_HPP_INCLUDED
