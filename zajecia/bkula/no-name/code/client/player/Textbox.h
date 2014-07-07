#ifndef __TEXTBOX_H__
#define __TEXTBOX_H__

#include "global_main.h"
#include "Area.h"
#include "ClickSystem.h"

// klasa narzędziowa
// do tworzenia pól tekstowych

class Textbox
{
public:

    Textbox(int _font_size, const Area& _area, string _default_text = "", const Color& _color = getGameColor(), bool _resizable = false);
    virtual ~Textbox();

    void draw();
    void update();

    void clearText() { text = ""; }
    string getText() const { return text; }

    void reInit(Area::Style s, float a1, float a2, float a3, float a4) throw(Error);
    void reInit(const Area& other);

protected:

    Area area;
    ClickSystem cs;

    string default_text;
    string text;
    bool resizable;
    int font_size;
    Color color;
    ClickSystem screenCS;
    bool active;
};

#endif // __TEXTBOX_H__
