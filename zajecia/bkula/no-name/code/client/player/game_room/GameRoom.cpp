#include "GameRoom.h"

GameRoom::GameRoom()
{
    //ctor
}

GameRoom::~GameRoom()
{
    //dtor
}

void GameRoom::update()
{
    //
}

void GameRoom::draw()
{
    al_clear_to_color(Color::white());

    al_draw_text(font(38), Color::black(), screen().cx(), screen().cy() - 38/2, ALLEGRO_ALIGN_CENTER, "Tu toczy się gra");
}
