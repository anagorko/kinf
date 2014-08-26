#ifndef __TEXTBOX_H__
#define __TEXTBOX_H__

#include "global_main.h"
#include "Area.h"
#include "ClickSystem.h"
#include <chrono>

/// klasa narzędziowa
/// do tworzenia pól tekstowych

/* narazie klasa Textbox jest pozbawiona następujących funkcjonalnoźci:
 - praca z tekstem w jednej linijce (nie reaguje na ENTER)
 - praca z tekstem szerszym niż textbox
 - zmiana działania strzałek w połączeniu z klawiszami shift i ctrl
 - polskie znaki (tylko częściowe problemy)
 */

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

private:

    bool active;

    Area area;
    ClickSystem cs;

    string default_text;
    string text;
    bool resizable;
    float font_size;
    Color color;
    ClickSystem screenCS;

    chrono::system_clock::time_point prev_time;
    bool show_cursor;
    pair<int,int> selection;
    bool selecting;
    int selection_was_started_from;
    int mouse_position();
    float cursor_x();

    struct KeyControler
    {
        KeyControler(int _myKeyID) :
            myKeyID(_myKeyID),
            isPressed(false),
            howManyTruths(0)
        {
            //
        }
        bool update()
        {
            if (key(myKeyID)) {
                if (!isPressed) {
                    isPressed = true;
                    startPressing = chrono::system_clock::now();
                    howManyTruths = 0;
                    return true;
                } else if (chrono::system_clock::now() > startPressing + chrono::milliseconds(450) + howManyTruths*chrono::milliseconds(45)) {
                    howManyTruths++;
                    return true;
                }
            } else {
                isPressed = false;
                return false;
            }
        }
    private:
        int howManyTruths;
        int myKeyID;
        chrono::system_clock::time_point startPressing;
        bool isPressed;
    };

    struct KeyChar
    {
        KeyChar(int _myKeyID, string _normal = "", string _withShift = "", string _withAltGr = "", string _withAltGrAndShift = "") :
            kc (_myKeyID),
            normal (_normal),
            withShift (_withShift == "" ? _normal : _withShift),
            withAltGr (_withAltGr),
            withAltGrAndShift (_withAltGrAndShift == "" ? _withAltGr : _withAltGrAndShift)
        {
            //
        }
        string update()
        {
            if (kc.update()) {
                if (key(ALLEGRO_KEY_LSHIFT) || key(ALLEGRO_KEY_RSHIFT) || capsLock()) {
                    if (key(ALLEGRO_KEY_ALTGR)) return withAltGrAndShift;
                    return withShift;
                }
                if (key(ALLEGRO_KEY_ALTGR)) return withAltGr;
                return normal;
            }
            return "";
        }
    private:
        KeyControler kc;
        string normal;
        string withShift;
        string withAltGr;
        string withAltGrAndShift;
    };

    vector<KeyChar> keychar;

    KeyControler kcLeft;
    KeyControler kcRight;
    KeyControler kcDelete;
    KeyControler kcBackspace;
};

#endif // __TEXTBOX_H__
