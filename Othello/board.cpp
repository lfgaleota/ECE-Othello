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
