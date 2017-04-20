#ifndef BACKUP_H_INCLUDED
#define BACKUP_H_INCLUDED

#include "../inc/board/gameboard.hpp"
#include <vector>
#include <fstream>

class BackupManager
{
private :

    fstream playerFile ;
    fstream boardFile ;

public :

    void SaveAPlayer();
    void SaveABoard();

};



#endif // BACKUP_H_INCLUDED
