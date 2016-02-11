#include "Bot.h"

bool Bot::receivePacket(Packet &payload) throw(Error)
{
    Packet::receivePacketTemplate(web_client, payload);
}

void Bot::sendCommand(Data::Commands command, string args) throw(Error)
{
    Packet::sendCommandTemplate(web_client, command, args);
}
