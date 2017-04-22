#include "Save.h"

Save::~Save()
{

}

//passer à un type booleen pour vérifier que la sauvegarde a réussi ?
void Save::savePlayer(Othello::Players::Human player_toSave, int slot)
{
    m_playerName = player_toSave.getName();

    std::ofstream players1("playerFile1.txt");
    std::ofstream players2("playerFile2.txt");
    std::ofstream players3("playerFile3.txt");

    switch(slot)
    {
    case 1 :

        players1 << m_playerName << std::endl ;

        break;

    case 2 :

        players2 << m_playerName << std::endl ;

        break;

    case 3 :

        players3 << m_playerName << std::endl ;

        break;

    default:

        break;

    }

    players1.close();
    players2.close();
    players3.close();
}

void Save::saveBoard(Othello::Board::GameBoard gameBoard_toSave, int slot)
{

}
