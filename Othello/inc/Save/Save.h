#ifndef SAVE_H_INCLUDED
#define SAVE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include "../players/human.hpp"
#include "../board/gameboard.hpp"

/// \class Save Save.h
class Save
{
private :

    std::string m_playerName ;

public :

    /// \fn saveBoard
    void saveBoard(Othello::Board::GameBoard gameBoard_toSave, int slot);
    /// \fn savePlayer
    void savePlayer(Othello::Players::Human player_toSave, int slot);

    /// \fn destructor
    ~Save();
};



#endif // SAVE_H_INCLUDED
