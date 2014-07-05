#include "ClickSystem.h"
#include "global.h"

void ClickSystem::update(const Position& _pos) throw(Error)
{
    pos = _pos;
    update();
}

void ClickSystem::update() throw(Error)
{
    if (!pos.ifInitialized()) throw Error(__FILE__, __LINE__, "Update niezainicjalizowango clicksystemu");

    if (mouse_pressed() && invaded) is_pressed = true;

    if ((!mouse_pressed()) && mouse_x() >= pos.x1() && mouse_x() <= pos.x2() && mouse_y() >= pos.y1() && mouse_y() <= pos.y2()) invaded = true;
    else invaded = false;

    if (!mouse_pressed()) {
        if (is_pressed && invaded) pressed = true;
        is_pressed = false;
    }
}

bool ClickSystem::click()
{
    if (!pressed) return false;
    pressed = false;
    return true;
}
