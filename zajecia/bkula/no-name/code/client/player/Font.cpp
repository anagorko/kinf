#include "Font.h"

using namespace std;

Font::Font() : path("arial.ttf"), minimal(8), maximal(128)
{
    //
}

ALLEGRO_FONT* Font::operator()(int n) throw(Error)
{
    if (n < minimal || n > maximal) {
        stringstream ss;
        ss << "Próba załadowania czcionki o rozmiarze " << n;
        throw Error(__FILE__, __LINE__, ss.str());
    }

    if (n >= v.size() + minimal) {
        for (int i = v.size() - n - minimal; i >= 0; --i) {
            v.push_back(NULL);
        }
    }

    v[n-minimal] = al_load_ttf_font(path.c_str(), n+minimal, 0);

    stringstream ss;
    ss << "Nie magę załadować czcionki " << path;
    if (!v[n-minimal]) throw Error(__FILE__, __LINE__, ss.str());

    return v[n-minimal];
}

Font f;
ALLEGRO_FONT* font(int n) { return f(n); }

