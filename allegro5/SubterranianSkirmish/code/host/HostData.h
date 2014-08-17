#ifndef __HOSTDATA_H__
#define __HOSTDATA_H__

#include "../Data.h"
using namespace std;

class HostData : public Data
{
public:

    HostData();
    ~HostData();

    // rozsyła dane do clientów
    void distribute();

    // aktualizuje grę
    void update();

    // iterator do gracza który jest hostem
    list<PlayerData>::iterator host_player;
};

#endif // __HOSTDATA_H__
