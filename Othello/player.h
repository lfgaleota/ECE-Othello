#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

using namespace std ;

class Player
{
protected :

    string m_name ;

public :

    Player();
    ~Player();

    virtual pair<int,int> ask_for_move();
};



#endif // PLAYER_H_INCLUDED
