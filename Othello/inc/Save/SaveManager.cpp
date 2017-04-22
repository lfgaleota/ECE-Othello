#include "SaveManager.h"

SaveManager::~SaveManager()
{

}

void SaveManager::save(Othello::Board::GameBoard gameBoard_toSave,Othello::Players::Human player_toSave,int slot)
{
    m_firstSlot.savePlayer(player_toSave,slot);


}
