#include "globalGraphic.h"

void drawGradient(Position pos, const Color& from, const Color& to, bool withFrame)
{
    for (float i = pos.y1(); i < pos.y2(); ++i) {
        al_draw_line(pos.x1(), i, pos.x2(), i, Color(from * ((pos.y2()-i)/pos.h()) + to * ((i-pos.y1())/pos.h())), 1.5);
    }

    if (withFrame) {
        al_draw_rectangle(POS(pos), Color::black(), 1.5);
    }
}
