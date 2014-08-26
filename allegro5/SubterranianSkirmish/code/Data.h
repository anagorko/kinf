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
        COM_JOIN_THE_GAME, // int ID, bool is_bot, string nick
        COM_LEAVE_THE_GAME, // int ID
        COM_START_THE_GAME, // [TYLKO_HOST]
        COM_ADD_BOT // [TYLKO_HOST]
    };

    // mozliwe stany w jakim znajduje się gra
    enum GameStates
    {
        WAITING,
        PAUZE,
        RUNNING,
        NON_EXISTANCE
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
        FC_DARK_GREEN,
        FC_MAX // ZAWSZE OSTATNIE, oznacza liczba kolorów (nie kolejny kolor)
    };

    // struktura reprezentująca dane pojedyńczego clienta
    struct PlayerData
    {
        const short ID;
        const bool is_bot;
        const string nick;
        const FlagColors flag_color;

        PlayerData(const short _ID, const bool& _is_bot, const string& _nick, const FlagColors& _flag_color)
            : ID(_ID), is_bot(_is_bot), nick(_nick), flag_color(_flag_color) {}
    };

    static const short MAX_NUMBER_OF_PLAYERS = 8;

    // lista graczy
    list<PlayerData> players;
};

#endif // __DATA_H__
