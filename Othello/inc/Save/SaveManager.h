#ifndef SAVEMANAGER_H_INCLUDED
#define SAVEMANAGER_H_INCLUDED

#include <iostream>
#include "Save.h"

class SaveManager
{
private :

    Save firstSlot ;
    Save secondSlot ;
    Save thirdSlot ;

public :

    SaveManager();
    ~SaveManager();

    save();
    load();
};



#endif // SAVEMANAGER_H_INCLUDED
