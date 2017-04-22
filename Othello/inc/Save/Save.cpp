#include "Save.h"

Save::~Save()
{

}

//passer à un type booleen pour vérifier que la sauvegarde a réussi ?
void Save::savePlayer(Othello::Players::Human player_toSave)
{
    std::ofstream players("playerFile.txt");

    players << player_toSave.getName() << std::endl ;

    players.close();

}

void Save::saveBoard(Othello::Board::GameBoard gameBoard_toSave)
{
    std::ofstream board("boardFile.txt");

    board << gameBoard_toSave.getBoard() << std::endl ;

    board.close();

}
