#ifndef __PACKET_H__
#define __PACKET_H__

// Klasa przechowująca dane o paczce
// paczki służą do komunikacji serwera z klientami: host, player lub bot

#include "Data.h"
#include "WebsocketsClient.h"

#include <sstream>
using namespace std;

class Packet
{
public:

    enum Types
    {
        DATA,
        COMMAND,
        CHAT
    };

    Packet(Types _type, string _args);
    Packet() {}

    Types type;
    stringstream args;

    static bool receivePacketTemplate(WebsocketsClient* web_client, Packet &payload) throw(Error);
    static void sendCommandTemplate(WebsocketsClient* web_client, Data::Commands command, string args = "") throw(Error);
};

#endif // __PACKET_H__
