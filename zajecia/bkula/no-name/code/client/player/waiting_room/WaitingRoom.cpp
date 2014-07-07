#include "WaitingRoom.h"

void(*WaitingRoom::whenClosed)() = NULL;

WaitingRoom::WaitingRoom(void(*_whenClosed)())
{
    whenClosed = _whenClosed;

    host_menu = new GroupOfButtons(screen().cx(), screen().cy(), "", 26);
    host_menu->addButton("Rozpocznij grę", []{/*COMMAND: START_GAME*/});
    host_menu->addButton("Dodaj bota", []{/*COMMAND: ADD_BOT*/});
    host_menu->addButton("Wyjdź", []{whenClosed();});

    client_menu = new GroupOfButtons(screen().cx(), screen().cy(), "", 26);
    client_menu->addButton("Wyjdź", []{whenClosed();});
}

WaitingRoom::~WaitingRoom()
{
    delete host_menu;
    delete client_menu;
}

void WaitingRoom::update()
{
    if (getServer() == "127.0.0.1") host_menu->update();
    else client_menu->update();
}

void WaitingRoom::draw()
{
    al_clear_to_color(Color::white());

    if (getServer() == "127.0.0.1") host_menu->draw();
    else client_menu->draw();
}
