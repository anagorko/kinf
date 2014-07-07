#ifndef GroupOfButtons_H
#define GroupOfButtons_H

#include "Button.h"
#include "Textbox.h"
#include <vector>

class GroupOfButtons
{
public:

    GroupOfButtons(int _cx, int _cy, string _title = "", int _font_size = 32, Color _default_color = getGameColor());

    void addButton(string _text, void(*_fn)(), Color _color = Color::null());
    void addTextbox(string* pText, string _default_text = "");

    void update();
    void draw();

private:

    string title;

    struct MyTextbox
    {
        MyTextbox(Textbox _box, string* _pText) : box(_box), pText(_pText) {}
        string* pText;
        Textbox box;
    };

    // true = button, false = textbox
    vector<bool> objectsSequence;

    vector<Button> buttons;
    vector<MyTextbox> textboxes;

    int cx, cy;

    int getW();
    int getH();

    int font_size;
    int space() { return font_size; }

    // wyliczane na podstawie font_size
    int button_w;
    const int button_h;

    bool centred_x, centred_y;

    Color default_color;
};

#endif // GroupOfButtons_H
