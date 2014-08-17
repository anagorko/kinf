#ifndef __Bot_H__
#define __Bot_H__

#include "../Client.h"

class Bot : public Client
{
public:

    Bot(string _server);
    virtual ~Bot() = 0;
    virtual void mainLoop() = 0;

protected:

    const string server;

    bool receivePacket(Packet &payload) throw(Error);
    void sendCommand(Data::Commands command, string args = "") throw(Error);
};

#endif // __Bot_H__
