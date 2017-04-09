#ifndef HUMAN_H_INCLUDED
#define HUMAN_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "player.h"

using namespace std ;

class Human : public Player
{
private :

    //dunno yet

public :

    pair<int,int> ask_for_move() ;
};


#endif // HUMAN_H_INCLUDED
