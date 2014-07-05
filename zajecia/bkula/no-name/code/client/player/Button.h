#ifndef Button_H
#define Button_H

#include "ClickSystem.h"
#include "Color.h"

class Button
{
public:

    // Kostruktor inicjalizujący
    Button(string _text, void(*_fn)(), Color _color, Position _pos);

    // Kostrkutor NIE inicjalizujący
    Button(string _text, void(*_fn)(), Color _color);

    void update();
    void draw();

    Position pos;

private:

    // wskaźnik na funkcję wywoływaną w momencie kliknięcia przycisku
    void(*fn)();

    string text;

    Color color;

    ClickSystem cs;

    void drawRectangle(int cx, int cy, int w, int h, const Color& a, const Color& b);
};

#endif // Button_H
