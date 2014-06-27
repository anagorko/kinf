#ifndef ClickSystem_H
#define ClickSystem_H

class ClickSystem {
public:

    ClickSystem ()
    : invaded(0), is_pressed(0), pressed(0)
    {
        //
    }

    ClickSystem (int _x1, int _y1, int _x2, int _y2)
    : invaded(0), is_pressed(0), pressed(0), x1(_x1), y1(_y1), x2(_x2), y2(_y2)
    {
        //
    }

    void update();

    void changeArea(int _x1, int _y1, int _x2, int _y2);

    bool click();

    bool getInvaded() const { return invaded; }
    bool getIsPressed() const { return is_pressed; }

private:

    int x1, y1, x2, y2;

    bool pressed;
    bool invaded;
    bool is_pressed;
};

#endif // ClickSystem_H
