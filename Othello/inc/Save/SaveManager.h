#ifndef SAVEMANAGER_H_INCLUDED
#define SAVEMANAGER_H_INCLUDED

#include <iostream>
#include "Save.h"

class SaveManager
{
private :

    Save firstSlot ;
    Save secondSlot ;
    Save thirdSlot ;

public :

    SaveManager();
    ~SaveManager();

    void save(Othello::Board::GameBoard gameBoard_toSave,Othello::Players::Human player_toSave, int slot);
    void load();
};



#endif // SAVEMANAGER_H_INCLUDED
