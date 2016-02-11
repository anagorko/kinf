#include "Textbox.h"

Textbox::Textbox(int _font_size, const Area& _area, string _default_text, const Color& _color, bool _resizable)
    : font_size(_font_size), area(_area), resizable(_resizable), text(""), default_text(_default_text),
      color(_color), active(false), cs(_area, ALLEGRO_SYSTEM_MOUSE_CURSOR_EDIT), screenCS(screen()),
      prev_time(chrono::system_clock::now()), selection(0,0), show_cursor(0), kcBackspace(ALLEGRO_KEY_BACKSPACE),
      kcDelete(ALLEGRO_KEY_DELETE), kcLeft(ALLEGRO_KEY_LEFT), kcRight(ALLEGRO_KEY_RIGHT), selecting(false)
{
    selection.first = 0;
    selection.second = 0;

    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        keychar.push_back(i);
    }

    for (int i = 0; i < 26; i++) {
        stringstream ss[2];
        ss[0] << char(97+i);
        ss[1] << char(65+i);
        keychar[i+1] = KeyChar(i+1, ss[0].str(), ss[1].str());
    }

    #define ADD(keycode) );keychar[keycode]=KeyChar(keycode,

    if(0 // nie ruszać, potrzebne

    ADD(ALLEGRO_KEY_A) "a","A","ą","Ą"
    ADD(ALLEGRO_KEY_C) "c","C","ć","Ć"
    ADD(ALLEGRO_KEY_E) "e","E","ę","Ę"
    ADD(ALLEGRO_KEY_L) "l","L","ł","Ł"
    ADD(ALLEGRO_KEY_N) "n","N","ń","Ń"
    ADD(ALLEGRO_KEY_O) "o","O","ó","Ó"
    ADD(ALLEGRO_KEY_S) "s","S","ś","Ś"
    ADD(ALLEGRO_KEY_X) "x","X","ź","Ź"
    ADD(ALLEGRO_KEY_Z) "z","Z","ż","Ż"

    ADD(ALLEGRO_KEY_0) "0",")"
    ADD(ALLEGRO_KEY_1) "1","!"
    ADD(ALLEGRO_KEY_2) "2","@"
    ADD(ALLEGRO_KEY_3) "3","#"
    ADD(ALLEGRO_KEY_4) "4","$"
    ADD(ALLEGRO_KEY_5) "5","%"
    ADD(ALLEGRO_KEY_6) "6","^"
    ADD(ALLEGRO_KEY_7) "7","&"
    ADD(ALLEGRO_KEY_8) "8","*"
    ADD(ALLEGRO_KEY_9) "9","("

    ADD(ALLEGRO_KEY_TILDE) "`", "~"
    ADD(ALLEGRO_KEY_MINUS) "-","_"
    ADD(ALLEGRO_KEY_EQUALS) "=","+"
    ADD(ALLEGRO_KEY_MINUS) "-","_"
    ADD(ALLEGRO_KEY_BACKSLASH) "\\","|"
    ADD(ALLEGRO_KEY_SEMICOLON) ";",":"
    ADD(ALLEGRO_KEY_QUOTE) "'","\""
    ADD(ALLEGRO_KEY_COMMA) ",","<"
    ADD(ALLEGRO_KEY_FULLSTOP) ".",">"
    ADD(ALLEGRO_KEY_SLASH) "/","?"
    ADD(ALLEGRO_KEY_SPACE) " "

    ); // nie ruszać, potrzebne

    #undef ADD
}

Textbox::~Textbox()
{
    //
}

void Textbox::update()
{
    cs.update();
    screenCS.update();

    if (!selecting && screenCS.getIsPressed()) {
        if (cs.getIsPressed()) {
            active = true;
            selecting = true;
            selection_was_started_from = mouse_position();
            selection.first = selection_was_started_from;
            selection.second = selection_was_started_from;
        } else {
            active = false;
            selecting = false;
            selection.first = 0;
            selection.second = 0;
        }
    }

    if (selecting) {

        selection.first = mouse_position();
        selection.second = selection_was_started_from;
        if (selection.first > selection.second) {
            swap(selection.first, selection.second);
        }

        if (!mouse_pressed()) {
            selecting = false;
            show_cursor = true;
            prev_time = chrono::system_clock::now();
        }
    }

    if (active) {

        for (KeyChar& k: keychar) {
            string insertion = k.update();
            if (!insertion.empty()) {
                text.replace(selection.first, selection.second - selection.first, insertion);
                show_cursor = true;
                prev_time = chrono::system_clock::now();
                if (selection.first == selection.second) {
                    selection.first = range(selection.second + static_cast<int>(insertion.size()), 0, static_cast<int>(text.size()));
                    selection.second = range(selection.second + static_cast<int>(insertion.size()), 0, static_cast<int>(text.size()));
                } else {
                    selection.second = ++selection.first;
                }
            }
        }

        // w 4 poniższych if-ach przydałoby się jeszcze dopisać co kiedy shift/ctrl jest wciśnięty
        if (kcLeft.update()) {
            show_cursor = true;
            prev_time = chrono::system_clock::now();
            if (selection.second != selection.first) {
                selection.second = selection.first;
            } else {
                selection.first = range(selection.first-1, 0, static_cast<int>(text.size()));
                selection.second = range(selection.second-1, 0, static_cast<int>(text.size()));
            }
        }
        if (kcRight.update()) {
            show_cursor = true;
            prev_time = chrono::system_clock::now();
            if (selection.first != selection.second) {
                selection.first = selection.second;
            } else {
                selection.first = range(selection.first+1, 0, static_cast<int>(text.size()));
                selection.second = range(selection.second+1, 0, static_cast<int>(text.size()));
            }
        }
        if (kcBackspace.update()) {
            show_cursor = true;
            prev_time = chrono::system_clock::now();
            if (selection.first != selection.second) {
                text.erase(selection.first, selection.second - selection.first);
                selection.second = range(selection.first, 0, static_cast<int>(text.size()));
            } else if (selection.first != 0) {
                text.erase(selection.first-1, 1);
                selection.first = range(selection.first-1, 0, static_cast<int>(text.size()));
                selection.second = range(selection.second-1, 0, static_cast<int>(text.size()));
            }
        }
        if (kcDelete.update()) {
            show_cursor = true;
            prev_time = chrono::system_clock::now();
            if (selection.first != selection.second) {
                text.erase(selection.first, selection.second - selection.first);
                selection.second = range(selection.first, 0, static_cast<int>(text.size()));
            } else if (selection.first != text.size()) {
                text.erase(selection.first, 1);
            }
        }

        if (chrono::system_clock::now() - prev_time >= chrono::milliseconds(400)) {
            show_cursor = show_cursor ? 0 : 1;
            prev_time = chrono::system_clock::now();
        }
    }
}

void Textbox::draw()
{
    al_draw_filled_rectangle(AREA, al_map_rgba(255,255,255,1));

    [=]{ // Lambda rysująca text
        int length = (text == "" ? default_text : text).size();
        float x = area.x() + font_size;
        const float y = area.y() + font_size;
        for (int i = 0; i < text.size(); ++i) {
            if (x + al_get_text_width(font(font_size), (text == "" ? default_text : text).substr(0, i+1).c_str()) >= area.x2()) {
                length = i;
                break;
            }
        }
        string text_to_draw = (text == "" ? default_text : text).substr(0, length);
        if (text == "") {
            al_draw_text(font(font_size), Color(200,200,200), x, y, ALLEGRO_ALIGN_LEFT, text_to_draw.c_str());
            return;
        }
        pair<int,int> s;
        s.first = range(selection.first, 0, length);
        s.second = range(selection.second, 0, length);
        string t = text_to_draw.substr(0, s.first);
        al_draw_text(font(font_size), Color::black(), x, y, ALLEGRO_ALIGN_LEFT, t.c_str());
        x += al_get_text_width(font(font_size), t.c_str());
        t = text_to_draw.substr(s.first, s.second - s.first);
        al_draw_filled_rectangle(x, y, x+al_get_text_width(font(font_size), t.c_str()), y+font_size, color);
        al_draw_text(font(font_size), color.ifDark() ? Color::white() : Color::black(), x, y, ALLEGRO_ALIGN_LEFT, t.c_str());
        x += al_get_text_width(font(font_size), t.c_str());
        t = text_to_draw.substr(s.second);
        al_draw_text(font(font_size), Color::black(), x, y, ALLEGRO_ALIGN_LEFT, t.c_str());
    }();

    //al_draw_rectangle(area.x1()+font_size/2, area.y1()+font_size/2, area.x2()-font_size/2, area.y2()-font_size/2, Color::white(), font_size);
    al_draw_filled_rectangle(area.x2()-font_size, area.y1(), area.x2(), area.y2(), Color::white());

    al_draw_rectangle(AREA, Color::black(), 1);

    if (cs.getInvaded() || cs.getIsPressed() || active) {

        int x = 7;
        for (float i = 0; i < x; ++i) {
            al_draw_rectangle(area.x1()+i, area.y1()+i, area.x2()-i, area.y2()-i, Color(0, 0, 0, 255-255*((i*2)/x)), 1);
        }

        if (active) {

            al_draw_rectangle(AREA, color, 3);
            if (show_cursor) {
                al_draw_line(cursor_x(), area.y() + font_size, cursor_x(), area.y() + font_size*2, Color::black(), font_size/10);
            }
        }
    }
}

void Textbox::reInit(const Area& other)
{
    area.reInit(other);
    cs.update(area);
}

void Textbox::reInit(Area::Style s, float a1, float a2, float a3, float a4) throw(Error)
{
    area.reInit(s, a1, a2, a3, a4);
    cs.update(area);
}

int Textbox::mouse_position()
{
    if (mouse_x() <= area.x() + font_size) return 0;
    if (mouse_x() >= area.x() + font_size + al_get_text_width(font(font_size),text.c_str())) return text.size();
    for (int i = 0; i < text.size(); i++) {
        if (mouse_x() > area.x() + font_size + al_get_text_width(font(font_size),text.substr(0, i).c_str()) &&
            mouse_x() < area.x() + font_size + al_get_text_width(font(font_size),text.substr(0, i+1).c_str())) {
            if (al_get_text_width(font(font_size),text.substr(i, 1).c_str())/2 >
                mouse_x() - (area.x() + font_size + al_get_text_width(font(font_size),text.substr(0, i).c_str()))) {
                return i;
            } else {
                return i+1;
            }
        }
    }
}

float Textbox::cursor_x()
{
    return area.x() + font_size + al_get_text_width(font(font_size), text.substr(0, selection_was_started_from == selection.first ? selection.second : selection.first).c_str());
}
