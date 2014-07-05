#include "Button.h"
#include "globalMain.h"
#include "globalGraphic.h"

Button::Button(string _text, void(*_fn)(), Color _color, Position _pos)
    : text(_text), color(_color), fn(_fn), pos(_pos), cs(_pos)
{
    //
}

Button::Button(string _text, void(*_fn)(), Color _color)
    : text(_text), color(_color), fn(_fn)
{
    //
}

void Button::update()
{
    cs.update(pos);
    if (cs.click()) fn();
}

void Button::draw()
{
    Color c = color;
    if (cs.getInvaded()) c += 65;
    else if (cs.getIsPressed()) c -= 65;

    drawGradient(pos, c + 50, c - 50);

    al_draw_text(font(pos.h()/3), [](bool b)->Color{return b ? Color::white() : Color::black();}(color.ifDark()),
                 pos.cx(), pos.cy() - pos.h()/6, ALLEGRO_ALIGN_CENTER, text.c_str());
}
