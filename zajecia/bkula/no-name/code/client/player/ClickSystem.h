#ifndef ClickSystem_H
#define ClickSystem_H

#include "Area.h"

class ClickSystem {
public:

    ClickSystem (const Area& = Area());

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
};

#endif // ClickSystem_H
