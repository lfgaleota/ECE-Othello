#ifndef SAVEMANAGER_H_INCLUDED
#define SAVEMANAGER_H_INCLUDED

#include <iostream>
#include "Save.h"

/// \class SaveManager SaveManager.h
class SaveManager
{
private :

    Save m_firstSlot ;
    Save m_secondSlot ;
    Save m_thirdSlot ;

public :

    /// \fn Destructor
    ~SaveManager();

    /// \fn save
    void save(Othello::Board::GameBoard gameBoard_toSave,Othello::Players::Human player_toSave, int slot);

};



#endif // SAVEMANAGER_H_INCLUDED
