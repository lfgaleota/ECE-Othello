#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "othello.h"

using namespace std ;

class Board
{
private :

    vector<vector<Pun>> m_game_board ; //plateau de jeu

public :

    Board();
    ~Board();

    vector<vector<Pun>> getBoard();

    pair<int,int> find_move(); // méthode qui renvoie une paire de coordonnées.
    void play(); //reçoit des coordonnées et ajoute un pion du joueur correspondant à l'endroit voulu ?
    void make_changes(); // fait les changements nécéssaires après un coup
};



#endif // BOARD_H_INCLUDED
