#ifndef __Player_H__
#define __Player_H__

#include "../Client.h"
#include "../../host/Host.h"
#include "waiting_room/WaitingRoom.h"
#include "game_room/GameRoom.h"

#include "Display.h"
#include "global_main.h"
#include "global_graphic.h"
#include "GroupOfButtons.h"

/// najważniejszy singleton w programie

class Player : public Client
{
public:

    Player();
    ~Player();

    // uruchamia główną pętlę programu
    void mainLoop();

    // obsuguje Error
    void handleError(const Error& err);

private:

    // kopia wskaźnika this
    static Player* this_copy;

    // funkcja powoduje zamknięcie gry
    static void closeGame() { this_copy->display->finish(); }

    // okno dostosowane do pracy z allegro
    Display* display;

    // jedyny obiekt typu Host w grze może być włączony lub wyłączony
    Host host;

    // dwie główne metody wywoływane w pętli nieskończonej:
    static void update(); // aktalizuje plansze, wysyła i odbiera paczki, reaguje na działanie gracza (mysz, klawisze, itp)
    static void draw(); // rysuje bierzącą sytuację w oknie

    // metoda odbiera wszystkie przychodzące paczki i je obsługuje
    void handleIncomingPackets();

    // funkcja uruchamia się w momencie zamknięcia okna z przyczyn zewnętrznych
    // np. Alt+f4 lub kliknięcie (x) w rogu okna
    // funkcja nie powinna się blokować!
    static void whenWindowClosed();

    // kolor gry
    Color gameColor;
    friend void setGameColor(const Color& color);
    friend Color getGameColor();

    // pokoje
    WaitingRoom* waiting_room;
    GameRoom game_room;

    // sceny
    enum Scene
    {
        MAIN_MENU,
        CREATING_THE_GAME,
        ATTACHING_TO_GAME,
        CONNECTION_FAILED,
        LEAVING_THE_GAME,
        ERROR_WINDOW
    };
    Scene scene;
    GroupOfButtons* main_menu;
    GroupOfButtons* attaching_to_game;
    GroupOfButtons* creating_the_game;
    GroupOfButtons* connection_failed;
    GroupOfButtons* leaving_the_game;
    GroupOfButtons* error_window;
    bool escWasPressed;

    // metoda łącząca z dadnym serverem i wyświetlająca okno w przypadku niepowodzenia
    string server_adress, my_nick;
    void tryConnectToServer(bool server_is_mine = false);

    // zwraca web_client->server
    friend string getServer();

    // paczki
    friend bool receivePacket(Packet &payload) throw(Error);
    friend void sendCommand(Data::Commands command, string args) throw(Error);

    // zwraca const referncje do obiektu *data
    friend const ClientData& getData() throw(Error);
};

#endif // __Player_H__
