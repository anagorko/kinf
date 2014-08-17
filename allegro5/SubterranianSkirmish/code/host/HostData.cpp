#include "HostData.h"

HostData::HostData()
    : host_player(players.begin())
{
    game_state = WAITING;
}

HostData::~HostData()
{
    //
}
