#ifndef __DATA_H__
#define __DATA_H__

// Klasa bazowa dla HostData i ClientData
// zawiera najważniejsze dane o stanie gry

#include <list>
#include <string>
using namespace std;

class Data
{
public:

    Data();
    virtual ~Data();

    // dostepne komendy modyfikujące dane
    enum Commands // prefix COM_
    {
        COM_JOIN_THE_GAME, // string nick
        COM_LEAVE_THE_GAME,
        COM_START_THE_GAME, // TYLKO_HOST
        COM_ADD_BOT // TYLKO_HOST
    };

    // mozliwe stany w jakim znajduję się gra
    enum GameStates
    {
        WAITING,
        PAUZE,
        RUNNING
    };

    GameStates game_state;

    // osiem kolorów flag
    enum FlagColors // prefix FC_
    {
        FC_RED,
        FC_DARK_BLUE,
        FC_BRIGHT_GREEN,
        FC_ORANGE,
        FC_PURPLE,
        FC_GREY,
        FC_BRIGHT_BLUE,
        FC_DARK_GREEN
    };

    // struktura reprezentująca dane pojedyńczego clienta
    struct PlayerData
    {
        string nick;
        FlagColors flag_color;
    };

    // lista graczy
    list<PlayerData> players;
};

#endif // __DATA_H__
