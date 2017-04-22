#include "Save.h"

/**
*@brief destructeur de la classe Save
**/
Save::~Save()
{

}

//passer à un type booleen pour vérifier que la sauvegarde a réussi ?
/**
*@brief fonction savePlayer
*@details permet de sauvegarder un joueur dans l'un des trois slots de sauvegarde.
**/
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

/**
*@brief fonction saveBoard
*@details permet de sauvegarder un plateau dans l'un des trois slots de sauvegarde.
**/
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

/**
*@brief fonction loadPlayer
*@details permet de charger un joueur depuis l'un des trois slots de sauvegarde.
**/
std::string Save::loadPlayer(int slot)
{
    std::ifstream player1("playerFile1.txt");
    std::ifstream player2("playerFile2.txt");
    std::ifstream player3("playerFile3.txt");

    std::string line ;

    switch(slot)
    {
    case 1 :

        getline(player1,line);
        break ;

    case 2 :

        getline(player2,line);
        break ;

    case 3 :

        getline(player3,line);
        break ;

    default :

        line = "randomPlayer" ;
        break ;
    }

    player1.close();
    player2.close();
    player3.close();

return line ;
}
