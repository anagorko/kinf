#include "GroupOfButtons.h"

GroupOfButtons::GroupOfButtons(int _cx, int _cy, string _title, int _font_size, Color _color)
    : cx(_cx), cy(_cy), title(_title), font_size(_font_size), color(_color),
     button_h(font_size+font_size*(2.0/3.0)), button_w(al_get_text_width(font(font_size), title.c_str()) + space*3)
{
    //
}

void GroupOfButtons::addButton(string _text, void(*_fn)())
{
    button_w = max(button_w, al_get_text_width(font(font_size), _text.c_str()) + space*3);

    objectsSequence.push_back(1);
    buttons.push_back(Button(_text, _fn, color, Position()));

    for (int i = 0, b = buttons.size(), t = textboxes.size(); i < objectsSequence.size(); ++i) {
        if (objectsSequence[i]) {
            buttons[--b].pos.reInit(Position::CXYWH, cx, cy + getH()/2 - (button_h+space)*(i+1) + button_h/2, button_w, button_h);
        } else {
            textboxes[--t].pos.reInit(Position::CXYWH, cx, cy + getH()/2 - (button_h+space)*(i+1) + button_h/2, button_w, button_h);
        }
    }
}

void GroupOfButtons::addTextbox(/**/)
{
    objectsSequence.push_back(0);
    //textboxes.push_back(Textbox());
}

void GroupOfButtons::update()
{
    for (auto& b: buttons) {
        b.update();
    }
    for (auto& t: textboxes) {
        t.update();
    }
}

void GroupOfButtons::draw()
{
    al_draw_filled_rectangle(cx - getW()/2, cy - getH()/2, cx + getW()/2, cy + getH()/2, Color(0,0,0,100));

    al_draw_text(font(font_size), Color::white(), cx, cy - getH()/2 + space, ALLEGRO_ALIGN_CENTER, title.c_str());

    for (auto& b: buttons) {
        b.draw();
    }
    for (auto& t: textboxes) {
        t.draw();
    }
}

int GroupOfButtons::getW()
{
    return button_w + space*2;
}

int GroupOfButtons::getH()
{
    return space + ((space+button_h) * objectsSequence.size()) + [=]{ return title == "" ? 0 : space*2 + font_size; }();
}
