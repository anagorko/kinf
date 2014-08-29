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

    // łączy się z serverem 127.0.0.1
    void connect() throw(Error);

    // dwie główne metody wywoływane w pętli nieskończonej
    void distribute(bool is_the_last_distribute = false) throw(Error); // rozsyła dane do clientów
    void update() throw(Error); // aktualizuje grę

private:

    WebsocketsClient* web_client;

    void executeCommands() throw(Error);
};

#endif // __HOSTDATA_H__
