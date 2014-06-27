#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "global.h"

// klasa narzędziowa
// do tworzenia pól tekstowych

class Textbox
{
public:

    Textbox(int _font_size, int _x, int _y, int _w, int _h, bool _centred = false, bool _resizable = false, string _text = "");
    virtual ~Textbox();

    void draw();
    void update();

    void clearText();
    string getText();

protected:

    string text;
    int x, y;
    int w, h;
    bool centred;
    bool resizable;
    int font_size;
};

#endif // TEXTBOX_H
