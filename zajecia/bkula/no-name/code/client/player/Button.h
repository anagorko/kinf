#ifndef Button_H
#define Button_H

#include "ClickSystem.h"
#include "Color.h"
#include "global_main.h"

class Button
{
public:

    // Kostruktor inicjalizujący
    Button(string _text, void(*_fn)(), Area _area, Color _color = getGameColor());

    // Kostrkutor NIE inicjalizujący
    Button(string _text, void(*_fn)(), Color _color = getGameColor());

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
