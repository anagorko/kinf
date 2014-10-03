#include "Client.h"

Client::Client()
    : web_client(NULL), data(NULL), myID(-1)
{
    //
}

Client::~Client()
{
    /* if (web_client) {
        web_client->sendPacket("SS " + to_string(Packet::COMMAND) + " " + to_string(Data::COM_LEAVE_THE_GAME) + " " + to_string(myID));
    } */

    delete web_client;
    delete data;
}
