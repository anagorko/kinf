#ifndef ClickSystem_H
#define ClickSystem_H

#include "Position.h"

class ClickSystem {
public:

    ClickSystem (const Position& _pos = Position())
        : invaded(0), is_pressed(0), pressed(0), pos(_pos)
    {
        //
    }

    void update(const Position& _pos) throw(Error);
    void update() throw(Error);

    bool click();

    bool getInvaded() const { return invaded; }
    bool getIsPressed() const { return is_pressed; }

    Position pos;

private:

    bool pressed;
    bool invaded;
    bool is_pressed;
};

#endif // ClickSystem_H
