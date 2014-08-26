#include "HostData.h"

#include "../Packet.h"

HostData::HostData() : web_client("127.0.0.1")
{
    //
}

HostData::~HostData()
{
    distribute(true);
}

void HostData::distribute(const bool is_the_last_distribute)
{
    stringstream ss;

    ss << "SS " << Packet::DATA;

    ss << " " << is_the_last_distribute;

    ss << players.size();
    for (auto p: players) {
        ss << " " << p.ID;
        ss << " " << p.is_bot;
        ss << " " << p.nick;
        ss << " " << p.flag_color;
    }

    // zawsze na końcu
    web_client.sendPacket(ss.str());
    while (1) {
        try {
            web_client.serviceWebsockets();
        } catch (const Error& err) {
            continue;
        }
        break;
    }
}

void HostData::receiveCommands()
{
    string packet;
    while (web_client.receivePacket(packet)) {

        stringstream ss;
        ss << packet;
        ss >> packet;
        if (packet != "SS") continue;
        int packet_type;
        ss >> packet_type;
        if (packet_type != Packet::COMMAND) continue;
        ss >> packet_type;

        switch (packet_type) {

        case COM_START_THE_GAME:

            game_state = RUNNING;
            break;

        case COM_ADD_BOT:

            // jeszcze nie zaimplementowane
            break;

        case COM_JOIN_THE_GAME:

            exit(13);
            int _ID;
            ss >> _ID;
            if (players.back().ID + 1 == _ID) {
                bool _is_bot;
                ss >> _is_bot;
                string _nick;
                ss >> _nick;
                bool is_reserved[FC_MAX];
                for (int i = 0; i < FC_MAX; i++) is_reserved[i] = false;
                for (auto p: players) is_reserved[p.flag_color] = true;
                int n = random() % (FC_MAX - players.size());
                for (int i = 0; i < FC_MAX; i++) {
                    if (!is_reserved[i]) {
                        if (n > 0) n--;
                        else {
                            players.push_back(PlayerData(_ID, _is_bot, _nick, static_cast<FlagColors>(i)));
                            break;
                        }
                    }
                }
            }
            break;

        case COM_LEAVE_THE_GAME:

            // ...
            break;

        default:

            break;

        }
    }
}

void HostData::update()
{
    receiveCommands();

    /// ...
}
