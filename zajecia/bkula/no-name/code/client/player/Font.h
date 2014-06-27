#ifndef Font_H
#define Font_H

#include <allegro_font.h>
#include <allegro_ttf.h>

#include <vector>
#include <string>
using namespace std;

#include "../../Error.h"
#include "global.h"

// Narzędziowy singleton do pobierania wkaźników na czcionki

class Font
{
public:

    friend ALLEGRO_FONT* font(int n);

    Font();
    ALLEGRO_FONT* operator()(int n) throw(Error);
    const int minimal;
    const int maximal;
    const string path;

private:

    vector<ALLEGRO_FONT*> v;
};

#endif // Font_H
