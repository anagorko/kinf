#ifndef GroupOfButtons_H
#define GroupOfButtons_H

#include "Button.h"
#include "Textbox.h"
#include <vector>

class GroupOfButtons
{
public:

    GroupOfButtons(int _cx, int _cy, string _title, Color _color = getGameColor(), int _font_size = 14);

    void addButton(string _text, void(*_fn)());
    void addTextbox(/**/);

    void update();
    void draw();

private:

    string title;

    // true = button, false = textbox
    vector<bool> objectsSequence;

    vector<Button> buttons;
    vector<Textbox> textboxes;

    int cx, cy;

    int font_size;

    // wyliczane na podstawie font_size
    int button_w, button_h;

    bool centred_x, centred_y;

    static const int space = 15;

    Color color;
};

#endif // GroupOfButtons_H
