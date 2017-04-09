#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "othello.hpp"

using namespace std;

class Board {
	private :

		vector<vector<Pun>> m_game_board; //plateau de jeu
		pair<int, int> _move; //euuuh ca on va voir si on le met vraiment là, pas sur
		set<pair<int, int>> m_empty_spots;
		vector<pair<int, int>> m_possible_moves;


	public :

		Board();

		~Board();

		vector<vector<Pun>> getBoard();

		void find_empty_spots( pair<int, int> _move ); //fonction de recherche des cases vides ayant un voisin.
		bool test_a_move( bool turn, pair<int, int> spot );

		void find_possible_moves( bool turn );

		void play( pair<int, int> _move,
				   bool turn ); //reçoit des coordonnées et ajoute un pion du joueur correspondant à l'endroit voulu ?
		void make_changes( pair<int, int> _move );
};


#endif // BOARD_H_INCLUDED
