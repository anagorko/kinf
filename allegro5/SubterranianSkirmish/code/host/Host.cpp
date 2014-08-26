#include "Host.h"

using namespace std;

Host::Host() : is_running(false)
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

    server.start();
    this_thread::yield();

    void (Host::*method)() = &Host::mainLoop;
    host_thread = async(launch::async, [=]{(this->*method)();});
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
        data.update();
        data.distribute();
        this_thread::yield();
    }
}
