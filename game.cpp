#include "game.h"

Game::Game()
    : m_turn(false)
{
    Board plateau ;
    m_board = plateau ;

}

Game::~Game()
{

}

void Game::display()
{

    for(unsigned int i=0; i<m_board.getBoard().size(); i++)
    {
        for(unsigned int j=0; j<m_board.getBoard()[i].size(); j++)
        {

            if(m_board.getBoard()[i][j]==black)
            {
                cout << "1" ;
            }else
            {
                if(m_board.getBoard()[i][j]==white)
                {
                    cout << "2" ;
                }else
                {
                    cout << "0" ;
                }

            }


        }

        cout << endl ;
    }
}
