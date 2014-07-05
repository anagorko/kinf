#ifndef Player_H
#define Player_H

#include "../Client.h"
#include "../../host/Host.h"
#include "waiting_room/WaitingRoom.h"
#include "game_room/GameRoom.h"

#include "Display.h"
#include "globalMain.h"
#include "GroupOfButtons.h"

/// najważniejszy singleton w programie

class Player : public Client
{
public:

    Player();
    ~Player();

    // uruchamia główną pętlę programu
    void mainLoop();

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

    // aktalizuje plansze, wysyła i odbiera paczki, reaguje na działanie gracza (mysz, klawisze, itp)
    static void update();

    // rysuje bierzącą sytuację w oknie
    static void draw();

    // funkcja uruchamia się w momencie zamknięcia okna z przyczyn zewnętrznych
    // np. Alt+f4 lub kliknięcie (x) w rogu okna
    // funkcja nie powinna się blokować!
    static void whenWindowClosed();

    // kolor gry
    Color gameColor;
    friend void setGameColor(const Color& color);
    friend Color getGameColor();

    // status gry
    enum GameStatus {WAITING, RUNNING, PAUZE};
    GameStatus status;

    // sceny
    WaitingRoom waiting_room;
    GameRoom game_room;

    // menu
    GroupOfButtons* menu;

    // zamykanie gry
    GroupOfButtons* closing_window;
    bool closing;

    class Menu
    {
        void update();
        void draw();
    };
};

#endif // Player_H
