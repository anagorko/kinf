#include "Host.h"

using namespace std;

Host::Host() : is_running(false), client("127.0.0.1")
{
    //
}

Host::~Host()
{
    stop();
}

void Host::start()
{
    if (is_running.load()) return;

    is_running.store(true);
    void (Host::*method)() = &Host::mainLoop;
    host_thread = async(launch::async, [=]{(this->*method)();});

    server.start();
}

void Host::stop()
{
    if (!is_running.load()) return;

    is_running.store(false);
    host_thread.wait();

    server.stop();
}

void Host::mainLoop()
{
    while (is_running.load()) {
        //
    }
}
