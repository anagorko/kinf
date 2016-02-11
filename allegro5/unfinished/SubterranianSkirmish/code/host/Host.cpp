#include "Host.h"

using namespace std;

Host::Host() : have_to_run(false)
{
    //
}

Host::~Host()
{
    stop();
}

void Host::start()
{
    if (have_to_run.load()) return;
    have_to_run.store(true);

    server.start();
    while (!server.isRunning()) {
        this_thread::yield();
    }

    void (Host::*method)() = &Host::mainLoop;
    host_thread = async(launch::async, [=]{(this->*method)();});
    this_thread::yield();
}

void Host::stop()
{
    if (!have_to_run.load()) return;

    have_to_run.store(false);
    host_thread.wait();

    server.stop();
}

void Host::mainLoop()
{
    data.connect();
    while (have_to_run.load()) {
        data.update();
        data.distribute();
        this_thread::yield();
    }
    data.distribute(true);
}
