#ifndef __WAITINGROOM_H__
#define __WAITINGROOM_H__

#include "../GroupOfButtons.h"
#include "../global_main.h"
#include "../global_graphic.h"

class WaitingRoom
{
public:

    WaitingRoom(void(*_whenClosed)());
    ~WaitingRoom();

    void update();
    void draw();

    static void(*whenClosed)();

private:

    Button* buttonClose;
    Button* buttonStart;
    Button* buttonAddBot;
    Button* buttonLeave;

    const int font_size;
};

#endif // __WAITINGROOM_H__
