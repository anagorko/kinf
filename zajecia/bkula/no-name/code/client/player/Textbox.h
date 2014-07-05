#ifndef __TEXTBOX_H__
#define __TEXTBOX_H__

#include "global.h"
#include "Position.h"

// klasa narzędziowa
// do tworzenia pól tekstowych

class Textbox
{
public:

    Textbox(int _font_size, int _x, const Position& _pos, bool _resizable = false, string _text = "");
    virtual ~Textbox();

    void draw();
    void update();

    void clearText();
    string getText();

    Position pos;

protected:

    string text;
    bool resizable;
    int font_size;
};

#endif // __TEXTBOX_H__
