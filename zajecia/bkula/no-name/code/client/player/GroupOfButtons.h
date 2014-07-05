#ifndef GroupOfButtons_H
#define GroupOfButtons_H

#include "Button.h"
#include "Textbox.h"
#include <vector>

class GroupOfButtons
{
public:

    GroupOfButtons(int _cx, int _cy, string _title, int _font_size = 32, Color _color = getGameColor());

    void addButton(string _text, void(*_fn)());
    void addTextbox(/**/);

    void update();
    void draw();

private:

    static const int space = 15;

    string title;

    // true = button, false = textbox
    vector<bool> objectsSequence;

    vector<Button> buttons;
    vector<Textbox> textboxes;

    int cx, cy;

    int getW();
    int getH();

    int font_size;

    // wyliczane na podstawie font_size
    int button_w;
    const int button_h;

    bool centred_x, centred_y;

    Color color;
};

#endif // GroupOfButtons_H
