#ifndef __WAITINGROOM_H__
#define __WAITINGROOM_H__

#include "../GroupOfButtons.h"

class WaitingRoom
{
public:

    WaitingRoom(void(*_whenClosed)());
    ~WaitingRoom();

    void update();
    void draw();

    static void(*whenClosed)();

private:

    GroupOfButtons* host_menu;
    GroupOfButtons* client_menu;
};

#endif // __WAITINGROOM_H__
