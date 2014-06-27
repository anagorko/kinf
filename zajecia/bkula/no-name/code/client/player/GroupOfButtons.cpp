#include "GroupOfButtons.h"

GroupOfButtons::GroupOfButtons(int _cx, int _cy, string _title, Color _color, int _font_size)
: cx(_cx), cy(_cy), title(_title), color(_color), font_size(_font_size), button_h(font_size+font_size*(2/3)), button_w(al_get_text_width(font(font_size), title.c_str()))
{
    //
}

void GroupOfButtons::addButton(string _text, void(*_fn)())
{
    objectsSequence.push_back(1);
    buttons.push_back(Button(
        cx - button_w/2,
        cy - button_h/2 + (space+button_h)*objectsSequence.size() + [=]()->int{ return title == "" ? 0 : space + font_size/2; }(),
        button_w,
        button_h,
        _text,
        color,
        _fn
    ));
    button_w = max(button_w, al_get_text_width(font(font_size), _text.c_str()));
    /// UWAGA: Błąd logiczny - przyciski dodane wcześniej mogą mieć mniejsze button_w
}

void GroupOfButtons::addTextbox(/**/)
{
    objectsSequence.push_back(0);
    //textboxes.push_back(/**/);
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
    al_draw_text(font(font_size), Color::white(), cx, cy - (space+button_h)*objectsSequence.size() + space, ALLEGRO_ALIGN_CENTER, title.c_str());

    int w = button_w + space*2;
    int h = ((space+button_h) * objectsSequence.size()) + [=]{ return title == "" ? 0 : space*2 + font_size; }();

    al_draw_filled_rectangle(cx - w/2, cy - h/2, cx + w/2, cy + h/2, Color(0,0,0,100));

    for (auto& b: buttons) {
        b.draw();
    }
    for (auto& t: textboxes) {
        t.draw();
    }
}
