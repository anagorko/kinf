#ifndef __CLIENT_DATA_H__
#define __CLIENT_DATA_H__

#include "../Data.h"
using namespace std;

class ClientData : public Data
{
public:

    ClientData(/**/);
    ~ClientData();

    list<PlayerData>::iterator me;
};

#endif // __CLIENT_DATA_H__
