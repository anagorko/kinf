#include "ClientData.h"

#include <sstream>

ClientData::ClientData(const short& myID, const string& packet)
{
    stringstream ss;
    ss << packet;

    bool is_the_last_distribute;
    ss >> is_the_last_distribute;
    if (is_the_last_distribute) {
        // ...
    }

    short how_many_players;
    ss >> how_many_players;
    for (int i = 0; i < how_many_players; i++) {
        int _ID; ss >> _ID;
        bool _is_bot; ss >> _is_bot;
        string _nick; ss >> _nick;
        int _flag_color; ss >> _flag_color;
        players.push_back(PlayerData(_ID, _is_bot, _nick, static_cast<FlagColors>(_flag_color)));
        if (_ID == myID) me = players.end()--;
    }
}

ClientData::~ClientData()
{
    //
}
