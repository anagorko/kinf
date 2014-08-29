#ifndef __CLIENT_DATA_H__
#define __CLIENT_DATA_H__

#include "../Data.h"

#include <string>
using namespace std;

class ClientData : public Data
{
public:

    ClientData(const short& myID, const string& packet);
    ~ClientData();

    // iterator do danych o mnie
    list<PlayerData>::iterator me;
};

#endif // __CLIENT_DATA_H__
