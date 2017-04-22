#ifndef SAVE_H_INCLUDED
#define SAVE_H_INCLUDED

#include <iostream>
#include <fstream>
#include "../players/human.hpp"
#include "../board/gameboard.hpp"

/// \class Save Save.h
class Save
{
private :

    Othello::Players::Human m_player_save ;
    Othello::Board::GameBoard m_gameBoard_save ;

public :

    /// \fn saveBoard
    void saveBoard(Othello::Board::GameBoard gameBoard_toSave);
    /// \fn savePlayer
    void savePlayer(Othello::Players::Human player_toSave);

    /// \fn destructor
    ~Save();
};



#endif // SAVE_H_INCLUDED
