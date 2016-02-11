#include "Packet.h"

Packet::Packet(Types _type, string _args)
    : type(_type), args(_args)
{
    //
}

bool Packet::receivePacketTemplate(WebsocketsClient* web_client, Packet &payload) throw(Error)
{
    if (!web_client) {
        return false;
    }

    string p;
    if (web_client->receivePacket(p)) {

        stringstream ss;
        ss << p;
        ss >> p;
        if (p != "SS") throw Error(__FILE__, __LINE__, "Odebrałem nierozpoznaną paczkę");
        int n;
        ss >> n;
        switch (n) {
        case Packet::DATA: payload.type = Packet::DATA; break;
        case Packet::COMMAND: payload.type = Packet::COMMAND; break;
        case Packet::CHAT: payload.type = Packet::CHAT; break;
        default: throw Error(__FILE__, __LINE__, "Nierozpoznany typ paczki"); break;
        }
        string txt;
        txt = ss.str();
        txt.erase(txt.begin(), txt.begin() + 5);
        payload.args = txt;
        return true;

    } else {
        return false;
    }
}

void Packet::sendCommandTemplate(WebsocketsClient* web_client, Data::Commands command, string args) throw(Error)
{
    try {
        if (!web_client) {
            throw Error(__FILE__, __LINE__, "Próba wysłania paczki bez połączenia z serverem");
        }
    } catch (Error err) {
        return;
    }

    web_client->sendPacket("SS " + to_string(command) + " " + args);
}
