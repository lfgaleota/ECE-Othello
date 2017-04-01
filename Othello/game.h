#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "board.h"

class Game
{
private :

    int m_turn ; //player turn ?
    Board m_board ; //game board

public :

    Game();
    ~Game();

    void display();


};



#endif // GAME_H_INCLUDED
