#include "GroupOfButtons.h"
#include "global_graphic.h"

GroupOfButtons::GroupOfButtons(int _cx, int _cy, string _title, int _font_size, Color _default_color)
    : cx(_cx), cy(_cy), title(_title), font_size(_font_size), default_color(_default_color),
     button_h(font_size*3), button_w(al_get_text_width(font(font_size), title.c_str()) + space())
{
    //
}

void GroupOfButtons::addButton(string _text, void(*_fn)(), Color _color)
{
    button_w = max(button_w, al_get_text_width(font(font_size), _text.c_str()) + space()*5);

    objectsSequence.push_back(1);
    buttons.push_back(Button(_text, _fn, Area(), [=]()->Color{return _color == Color::null() ? default_color : _color;}()));

    for (int i = 0, b = buttons.size(), t = textboxes.size(); i < objectsSequence.size(); ++i) {
        if (objectsSequence[objectsSequence.size()-i-1]) {
            buttons[--b].reInit(Area::CXYWH, cx, cy + getH()/2 - (button_h+space())*(i+1) + button_h/2, button_w, button_h);
            buttons[b].reInit(Area::CXYWH, cx, cy + getH()/2 - (button_h+space())*(i+1) + button_h/2, button_w, button_h);
        } else {
            textboxes[--t].box.reInit(Area::CXYWH, cx, cy + getH()/2 - (button_h+space())*(i+1) + button_h/2, button_w, button_h);
            textboxes[t].box.reInit(Area::CXYWH, cx, cy + getH()/2 - (button_h+space())*(i+1) + button_h/2, button_w, button_h);
        }
    }
}

void GroupOfButtons::addTextbox(string* pText, string _text)
{
    button_w = max(button_w, al_get_text_width(font(font_size), _text.c_str()) + space()*5);

    objectsSequence.push_back(0);
    textboxes.push_back(MyTextbox(Textbox(font_size, Area(), _text, default_color, false), pText));

    for (int i = 0, b = buttons.size(), t = textboxes.size(); i < objectsSequence.size(); ++i) {
        if (objectsSequence[objectsSequence.size()-i-1]) {
            buttons[--b].reInit(Area::CXYWH, cx, cy + getH()/2 - (button_h+space())*(i+1) + button_h/2, button_w, button_h);
            buttons[b].reInit(Area::CXYWH, cx, cy + getH()/2 - (button_h+space())*(i+1) + button_h/2, button_w, button_h);
        } else {
            textboxes[--t].box.reInit(Area::CXYWH, cx, cy + getH()/2 - (button_h+space())*(i+1) + button_h/2, button_w, button_h);
            textboxes[t].box.reInit(Area::CXYWH, cx, cy + getH()/2 - (button_h+space())*(i+1) + button_h/2, button_w, button_h);
        }
    }
}

void GroupOfButtons::update()
{
    for (auto& b: buttons) {
        b.update();
    }
    for (auto& t: textboxes) {
        t.box.update();
        *(t.pText) = t.box.getText();
    }
}

void GroupOfButtons::draw()
{
    drawGradient(Area(Area::CXYWH, cx, cy, getW(), getH()), Color(0,0,0,100), Color(0,0,0,0));

    al_draw_text(font(font_size), Color::white(), cx, cy - getH()/2 + space()*1.5 - font_size/2, ALLEGRO_ALIGN_CENTER, title.c_str());

    for (auto& b: buttons) {
        b.draw();
    }
    for (auto& t: textboxes) {
        t.box.draw();
    }
}

int GroupOfButtons::getW()
{
    return button_w + space()*2;
}

int GroupOfButtons::getH()
{
    return space() + ((space()+button_h) * objectsSequence.size()) + [=]{ return title == "" ? 0 : space() + font_size; }();
}
