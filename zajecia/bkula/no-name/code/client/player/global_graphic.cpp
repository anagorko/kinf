#include "global_graphic.h"

#include "allegro_primitives.h"

void drawGradient(Area area, const Color& from, const Color& to, bool withFrame)
{
    for (float i = area.y1(); i < area.y2(); ++i) {
        al_draw_line(area.x1(), i, area.x2(), i, Color(from * ((area.y2()-i)/area.h()) + to * ((i-area.y1())/area.h())), 1.5);
    }

    if (withFrame) {
        al_draw_rectangle(AREA, Color::black(), 1.5);
    }
}
