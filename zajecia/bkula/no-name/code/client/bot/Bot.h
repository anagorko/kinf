#ifndef __Bot_H__
#define __Bot_H__

#include "../Client.h"

class Bot : public Client
{
    Bot(string _server);
    ~Bot();
    void mainLoop();

private:

    string server;
};

#endif // __Bot_H__
