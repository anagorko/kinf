#ifndef Button_H
#define Button_H

#include "ClickSystem.h"
#include "Color.h"

class Button
{
public:

    // Kostruktor inicjalizujący
    Button(string _text, void(*_fn)(), Color _color, Area _area);

    // Kostrkutor NIE inicjalizujący
    Button(string _text, void(*_fn)(), Color _color);

    void update();
    void draw();

    void reInit(Area::Style s, float a1, float a2, float a3, float a4) throw(Error);
    void reInit(const Area& other);

private:

    Area area;
    ClickSystem cs;

    // wskaźnik na funkcję wywoływaną w momencie kliknięcia przycisku
    void(*fn)();

    string text;

    Color color;
};

#endif // Button_H
