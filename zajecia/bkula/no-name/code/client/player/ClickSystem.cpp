#include "ClickSystem.h"
#include "global.h"

void ClickSystem::update()
{
    if (mouse_pressed() && invaded) is_pressed = true;

    if ((!mouse_pressed()) && mouse_x() >= x1 && mouse_x() <= x2 && mouse_y() >= y1 && mouse_y() <= y2) invaded = true;
    else invaded = false;

    if (!mouse_pressed()) {
        if (is_pressed && invaded) pressed = true;
        is_pressed = false;
    }
}

void ClickSystem::changeArea(int _x1, int _y1, int _x2, int _y2)
{
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;
}

bool ClickSystem::click()
{
    if (!pressed) return false;
    pressed = false;
    return true;
}
