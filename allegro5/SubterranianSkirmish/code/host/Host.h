#ifndef Host_H
#define Host_H

#include <atomic>
#include <future>
using namespace std;

#include <ctime>
#include <cstdlib>
#include <unistd.h>

#include "WebsocketsServer.h"
#include "../WebsocketsClient.h"
#include "HostData.h"
#include "../client/ClientData.h"

class Host
{
public:

    Host();
    ~Host();

    void start();
    void start(const ClientData& data);
    void stop();

private:

    atomic<bool> have_to_run;
    future<void> host_thread;

    WebsocketsServer server;

    void mainLoop();

    HostData data;
};

#endif // Host_H
