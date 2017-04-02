#include "board.h"

Board::Board()
    : m_game_board( 8, vector<Pun>( 8 ) )
{
    for(unsigned int i=0; i<m_game_board.size(); i++)
    {
        for(unsigned int j=0; j<m_game_board[i].size(); j++)
        {
            if((i==3&&j==3)||(i==4&&j==4))
            {
                m_game_board[i][j]= black ;
            } else
            {
                if((i==3&&j==4)||(i==4&&j==3))
                {
                    m_game_board[i][j]= white ;
                }
                else
                {
                    m_game_board[i][j]= blank ;
                }
            }
        }
    }
}



Board::~Board()
{

}

vector<vector<Pun>> Board::getBoard()
{
    return m_game_board ;
}

void Board::play(pair<int,int> _move,vector<pair<int,int>> possible_moves, bool turn)
{
    //je ne sais pas si on fera cette partie ici ou au moment de la sélection du coup, on en reparlera.

    //on vérifie que le mouvement est autorisé
    bool _continue = false ;

    for(unsigned int i=0;i<possible_moves.size();i++)
    {
        if(possible_moves[i]==_move)
        {
            _continue = true ;
        }
    }

    if(_continue) //ICI c'est le bout important, c'est l'assignation d'une nouvelle case
    {
        if(turn)
            m_game_board[_move.first][_move.second] = black ;
        else
            m_game_board[_move.first][_move.second] = white ;

    }else
    {
        //une exception qui renvoie au choix de mouvement ?
    }

    //ICI on appelle le changement de couleur nananana
    make_changes(_move);



}

void Board::make_changes(pair<int,int> _move)
{
    //on parcourt dans toutes les directions pour voir si il y a des pièces à changer. Je sais juste pas trop comment faire encore. je réfléchis.




}
