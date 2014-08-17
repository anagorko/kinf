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

class Host
{
public:

    Host();
    ~Host();

    void start();
    void stop();

private:

    atomic<bool> is_running;
    future<void> host_thread;

    WebsocketsServer server;
    WebsocketsClient client;

    void mainLoop();

    HostData data;
};

#endif // Host_H
