#ifndef BACKUP_H_INCLUDED
#define BACKUP_H_INCLUDED

#include "../board/gameboard.hpp"
#include <vector>
#include <fstream>

class BackupManager
{
private :

    std::string playerFile ;
    std::string boardFile ;

public :

    BackupManager();
    ~BackupManager();

    void SaveInASlot();


};



#endif // BACKUP_H_INCLUDED
