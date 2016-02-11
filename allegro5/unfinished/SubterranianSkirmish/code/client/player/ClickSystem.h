#ifndef ClickSystem_H
#define ClickSystem_H

#include "Area.h"
#include "global_main.h"
#include "global_graphic.h"

class ClickSystem {
public:

    ClickSystem (const Area& _area = Area(), ALLEGRO_SYSTEM_MOUSE_CURSOR _cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_NONE);

    void update(const Area& _area) throw(Error);
    void update() throw(Error);

    bool click();

    bool getInvaded() const { return invaded; }
    bool getIsPressed() const { return is_pressed; }

    Area area;

private:

    bool pressed;
    bool invaded;
    bool is_pressed;

    ALLEGRO_SYSTEM_MOUSE_CURSOR cursor;
};

#endif // ClickSystem_H
