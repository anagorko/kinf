#include "ClickSystem.h"

ClickSystem::ClickSystem (const Area& _area, ALLEGRO_SYSTEM_MOUSE_CURSOR _cursor)
    : invaded(0), is_pressed(0), pressed(0), area(_area), cursor(_cursor)
{
    //
}

void ClickSystem::update(const Area& _area) throw(Error)
{
    area = _area;
    update();
}

void ClickSystem::update() throw(Error)
{
    if (!area.ifInitialized()) throw Error(__FILE__, __LINE__, "Update niezainicjalizowango clicksystemu");

    if (mouse_pressed() && invaded) is_pressed = true;

    if ((!mouse_pressed()) && mouse_x() >= area.x1() && mouse_x() <= area.x2() && mouse_y() >= area.y1() && mouse_y() <= area.y2()) invaded = true;
    else invaded = false;

    if (!mouse_pressed()) {
        if (is_pressed && invaded) pressed = true;
        is_pressed = false;
    }

    if (cursor != ALLEGRO_SYSTEM_MOUSE_CURSOR_NONE && (getIsPressed() || getInvaded())) setMouseCursor(cursor);
}

bool ClickSystem::click()
{
    if (!pressed) return false;
    pressed = false;
    return true;
}
