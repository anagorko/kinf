#include "Color.h"

Color Color::black() { return Color(0,0,0); }
Color Color::white() { return Color(255,255,255); }

Color::Color(int _r, int _g, int _b, int _a) : r(_r), g(_g), b(_b), a(_a)
{
    //
}

Color::Color(int* p) throw(Error)
{
    if (sizeof(p) / sizeof(int) == 3) {
        r = p[0], g = p[1], b = p[2];
    } else if (sizeof(p) / sizeof(int) == 4) {
        r = p[0], g = p[1], b = p[2], a = p[3];
    } else {
        string statement = "Podano wskaźnik na tablicę o rozmiarze " + sizeof(p) / sizeof(int);
        throw Error(__FILE__, __LINE__, statement);
    }
}

Color::operator ALLEGRO_COLOR()
{
    return a == 255 ? al_map_rgb(r,g,b) : al_map_rgba(r,g,b,a);
}

bool Color::ifDark()
{
    return (r+g+b) < (255*3) / 2 ? true : false;
}

int& Color::operator[](int i) throw(Error)
{
    switch(i) {
    case 0: return r; break;
    case 1: return g; break;
    case 2: return b; break;
    case 3: return a; break;
    default:
    string statement = "Pytanie o nie istniejący parametr nr." + i;
    throw Error(__FILE__, __LINE__, statement);
    break;
    }
}

// preinkrementacja
Color Color::operator++()
{
    ++r, ++g, ++b;
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    return *this;
}

// postinkrementacja
Color Color::operator++(int)
{
    Color result = *this;
    ++(*this);
    return result;
}

// predekrementacja
Color Color::operator--()
{
    --r, --g, --b;
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
    return *this;
}

// postdekrementacja
Color Color::operator--(int)
{
    Color result = *this;
    --(*this);
    return result;
}

bool Color::operator==(const Color& other)
{
    return (r == other.r) && (g == other.g) && (b = other.b) && (a == other.a) ? true : false;
}

bool Color::operator!=(const Color& other)
{
    return (r == other.r) && (g == other.g) && (b = other.b) && (a == other.a) ? false : true;
}

Color Color::operator+=(const int& n)
{
    for (int i = 0; i < n; ++i) ++(*this);
    return *this;
}

Color Color::operator-=(const int& n)
{
    for (int i = 0; i < n; ++i) --(*this);
    return *this;
}
