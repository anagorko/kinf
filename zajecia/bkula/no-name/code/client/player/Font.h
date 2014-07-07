#ifndef __Font_H__
#define __Font_H__

#include <allegro_font.h>
#include <allegro_ttf.h>

#include <vector>
#include <string>
using namespace std;

#include "../../Error.h"
#include "global_main.h"

// Narzędziowy singleton do pobierania wkaźników na czcionki

class Font
{
public:

    friend ALLEGRO_FONT* font(int n);

    Font();
    ALLEGRO_FONT* operator()(int n) throw(Error);
    static const int MINIMAL = 8;
    static const int MAXIMAL = 128;
    const string font_name;

private:

    vector<ALLEGRO_FONT*> v;
};

#endif // __Font_H__
