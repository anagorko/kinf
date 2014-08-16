#ifndef __Bot_H__
#define __Bot_H__

#include "../Client.h"

class Bot : public Client
{
    Bot(string _server);
    virtual ~Bot() = 0;
    virtual void mainLoop() = 0;

private:

    const string server;
};

#endif // __Bot_H__
