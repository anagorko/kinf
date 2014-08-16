#include "WaitingRoom.h"

void(*WaitingRoom::whenClosed)() = NULL;

WaitingRoom::WaitingRoom(void(*_whenClosed)())
    : font_size(Scale::bk(21))
{
    whenClosed = _whenClosed;

    float x = screen().x2();
    #define ADD_BUTTON(name,txt,fn,color) \
    x -= font_size*3 + al_get_text_width(font(font_size), txt); \
    name = new Button(txt, fn, Area(Area::XYWH, x, font_size, al_get_text_width(font(font_size), txt) + font_size*2, font_size*3), Color::color()-135);
    ADD_BUTTON(buttonClose, "Zamknij grę", []{whenClosed();}, red)
    ADD_BUTTON(buttonAddBot, "Dodaj bota", []{;}, blue)
    ADD_BUTTON(buttonStart, "Rozpocznij grę", []{;}, green)
    x = screen().x2();
    ADD_BUTTON(buttonLeave, "Opuść grę", []{whenClosed();}, red)
    #undef ADD_BUTTON
}

WaitingRoom::~WaitingRoom()
{
    delete buttonClose;
    delete buttonStart;
    delete buttonAddBot;
    delete buttonLeave;
}

void WaitingRoom::update()
{
    if (getServer() == "127.0.0.1") {
        buttonStart->update();
        buttonAddBot->update();
        buttonClose->update();
    } else {
        buttonLeave->update();
    }
}

void WaitingRoom::draw()
{
    drawGradient(screen(), Color::white(), Color::yellow()+80, false);
    drawGradient(Area(Area::XYXY, 0, 0, screen().w(), font_size*5/2), Color(0,0,0,150), Color(0,0,0,90), false);
    drawGradient(Area(Area::XYXY, 0, font_size*5/2, screen().w(), font_size*5), Color(0,0,0,90), Color(0,0,0,150), false);
    drawGradient(Area(Area::XYWH, 0, font_size*5, screen().w(), font_size/4), Color(127,127,127), Color(255,255,255), false);
    drawGradient(Area(Area::XYWH, 0, font_size*5 + font_size/4, screen().w(), font_size/4), Color(255,255,255), Color(127,127,127), false);
    al_draw_text(font(font_size), Color::white(), font_size, font_size*2, ALLEGRO_ALIGN_LEFT, []{return "Połączono z " + getServer();}().c_str());
    al_draw_text(font(font_size*2), Color::black(), screen().cx(), screen().cy(), ALLEGRO_ALIGN_CENTER, "Tu pojawi się lista graczy");

    if (getServer() == "127.0.0.1") {
        buttonStart->draw();
        buttonAddBot->draw();
        buttonClose->draw();
    } else {
        buttonLeave->draw();
    }
}
