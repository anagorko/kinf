#ifndef Button_H
#define Button_H

#include "ClickSystem.h"
#include "Color.h"

class Button
{
public:

    Button(int _x, int _y, int _w, int _h, string _text, Color _color, void(*_fn)());

    void update();
    void draw();

private:

    // wskaźnik na funkcję wywoływaną w momencie wciśnięcia przycisku
    void(*fn)();

    int x, y;
    int w, h;

    string text;

    Color color;

    ClickSystem cs;

    void drawRectangle(int cx, int cy, int w, int h, const Color& a, const Color& b);
};

#endif // Button_H
