#include "Save.h"

Save::~Save()
{

}

//passer à un type booleen pour vérifier que la sauvegarde a réussi ?
void Save::savePlayer(Othello::Players::Human player_toSave, int slot)
{

    std::ofstream players1("playerFile1.txt");
    std::ofstream players2("playerFile2.txt");
    std::ofstream players3("playerFile3.txt");

    switch(slot)
    {
    case 1 :

        players1 << player_toSave.getName() << std::endl ;

        break;

    case 2 :

        players2 << player_toSave.getName() << std::endl ;

        break;

    case 3 :

        players3 << player_toSave.getName() << std::endl ;

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
    std::ofstream board1("boardFile1.txt");
    std::ofstream board2("boardFile2.txt");
    std::ofstream board3("boardFile3.txt");

    switch(slot)
    {
    case 1 :

        //save the empty neighbors
        board1 << gameBoard_toSave.getEmptyNeighbors() << std::endl ;
        //save the count
        board1 << gameBoard_toSave.punCount(Othello::Board::Pun::white) << std::endl ;
        board1 << gameBoard_toSave.punCount(Othello::Board::Pun::black) << std::endl ;
        //save the board


        break;

    case 2 :

        board2 << gameBoard_toSave.getEmptyNeighbors() << std::endl ;
        board2 << gameBoard_toSave.punCount(Othello::Board::Pun::white) << std::endl ;
        board2 << gameBoard_toSave.punCount(Othello::Board::Pun::black) << std::endl ;

        break;

    case 3 :

        board3 << gameBoard_toSave.getEmptyNeighbors() << std::endl ;
        board3<< gameBoard_toSave.punCount(Othello::Board::Pun::white) << std::endl ;
        board3 << gameBoard_toSave.punCount(Othello::Board::Pun::black) << std::endl ;

        break;

    default:

        break;

    }



}
