#include "SaveManager.h"

SaveManager::~SaveManager()
{

}

void SaveManager::save(Othello::Board::GameBoard gameBoard_toSave,Othello::Players::Human player_toSave,int slot)
{
    switch(slot)
    {
    case 1:

        m_firstSlot.savePlayer(player_toSave,slot);
        m_firstSlot.saveBoard(gameBoard_toSave,slot);
        break ;

    case 2 :

        m_secondSlot.savePlayer(player_toSave,slot);
        m_secondSlot.saveBoard(gameBoard_toSave,slot);

        break ;

    case 3 :

        m_thirdSlot.savePlayer(player_toSave,slot);
        m_thirdSlot.saveBoard(gameBoard_toSave,slot);

        break ;

    default :

        break ;
    }



}
