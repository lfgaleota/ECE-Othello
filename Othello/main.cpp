#include "othello.h"
#include "board.h"
#include "game.h"

//ENORME idée, si on a le temps on fait un undo, on annule le coup qui vient d'être joué et on propose de le rejouer !


using namespace std;

int main()
{
    Game othello ;

    othello.display() ;
    return 0;
}
