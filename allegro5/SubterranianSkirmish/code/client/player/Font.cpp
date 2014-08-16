#include "Font.h"

using namespace std;

Font::Font() : font_name("arial.ttf")
{
    //
}

ALLEGRO_FONT* Font::operator()(int n) throw(Error)
{
    if (n < MINIMAL || n > MAXIMAL) {
        stringstream ss;
        ss << "Próba załadowania czcionki o rozmiarze " << n;
        throw Error(__FILE__, __LINE__, ss.str());
    }

    if (n >= v.size() + MINIMAL || v[n-MINIMAL] == NULL) {
        for (int i = n - MINIMAL - v.size(); i >= 0; --i) {
            v.push_back(NULL);
        }

        /** rozwiązanie chwilowe: */ v[n-MINIMAL] = al_load_ttf_font("/home/bkula/kinf/zajecia/bkula/no-name/load/arial.ttf", n, 0);

        //v[n-MINIMAL] = al_load_ttf_font([=]{return "../../../load/" + font_name;}().c_str(), n, 0);
        if (!v[n-MINIMAL]) {
            stringstream ss;
            ss << "Nie mogę załadować czcionki " << font_name;
            throw Error(__FILE__, __LINE__, ss.str());
        }
    }

    return v[n-MINIMAL];
}

Font f;
ALLEGRO_FONT* font(int n) { return f(n); }

