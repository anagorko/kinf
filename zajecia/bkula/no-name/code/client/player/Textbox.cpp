#include "Textbox.h"

Textbox::Textbox(int _font_size, const Area& _area, string _default_text, const Color& _color, bool _resizable)
    : font_size(_font_size), area(_area), resizable(_resizable), text(""), default_text(_default_text),
      color(_color), active(false), cs(_area), screenCS(screen())
{
    //
}

Textbox::~Textbox()
{
    //
}

void Textbox::update()
{
    cs.update();
    screenCS.update();

    if (screenCS.click()) active = false;
    if (cs.click()) active = true;

    if (active) {

        // TUTAJ ODCZYT Z KLAWIATURY
    }
}

void Textbox::draw()
{
    al_draw_filled_rectangle(AREA, al_map_rgba(255,255,255,1));
    al_draw_rectangle(AREA, Color::black(), 1);

    if (cs.getInvaded() || cs.getIsPressed() || active) {

        int x = 7;
        for (float i = 0; i < x; ++i) {
            al_draw_rectangle(area.x1()+i, area.y1()+i, area.x2()-i, area.y2()-i, Color(0, 0, 0, 255-255*((i*2)/x)), 1);
        }

        if (active) {
            al_draw_rectangle(AREA, color, 3);
        }
    }

    al_draw_text(font(font_size), [=]{ return text == "" ? Color(127,127,127,170) : Color::black(); }(), area.x() + font_size, area.y() + font_size, ALLEGRO_ALIGN_LEFT, [=]{ return text == "" ? default_text : text; }().c_str());
}

void Textbox::reInit(const Area& other)
{
    area.reInit(other);
    cs.update(area);
}

void Textbox::reInit(Area::Style s, float a1, float a2, float a3, float a4) throw(Error)
{
    area.reInit(s, a1, a2, a3, a4);
    cs.update(area);
}
