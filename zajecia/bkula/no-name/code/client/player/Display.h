#ifndef Display_H
#define Display_H

#include "global.h"

class Display
{
public:

    Display() throw(Error);
    ~Display();

    // główna pętla gry
    void eventLoop(void(*update)(), void(*draw)(), void(*whenWindowClosed)());

    // zamyka okno
    void finish() { closed = true; }

    // zaprzyjaźnine funkcje globalne
    friend int screen_w();
    friend int screen_h();
    friend bool key(int n) throw(Error);
    friend int mouse_x();
    friend int mouse_y();
    friend bool mouse_pressed();
    friend void backToDisplay();

private:

    static Display* this_copy;

    bool key[ALLEGRO_KEY_MAX];
    int mouse_x;
    int mouse_y;
    bool mouse_pressed;

    const float FPS;

    ALLEGRO_DISPLAY_MODE display_mode;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE * event_queue;
    ALLEGRO_TIMER* timer;

    int SCREEN_W, SCREEN_H;

    bool closed;
};

#endif // Display_H
