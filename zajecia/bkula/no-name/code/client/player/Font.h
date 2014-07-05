#ifndef Font_H
#define Font_H

#include <allegro_font.h>
#include <allegro_ttf.h>

#include <vector>
#include <string>
using namespace std;

#include "../../Error.h"
#include "globalMain.h"

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

#endif // Font_H
