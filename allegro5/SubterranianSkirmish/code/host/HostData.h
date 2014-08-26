#ifndef __HOSTDATA_H__
#define __HOSTDATA_H__

#include "../Data.h"
#include "../WebsocketsClient.h"
using namespace std;

class HostData : public Data
{
public:

    HostData();
    ~HostData();

    // dwie główne metody wywoływane w pętli nieskończonej
    void distribute(bool is_the_last_distribute = false); // rozsyła dane do clientów
    void update(); // aktualizuje grę

private:

    WebsocketsClient web_client;

    void receiveCommands();
};

#endif // __HOSTDATA_H__
