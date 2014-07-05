#include "Color.h"
#include "globalMath.h"

Color Color::null() { return Color(0,0,0,0); }
Color Color::black() { return Color(0,0,0); }
Color Color::white() { return Color(255,255,255); }

Color::Color(int _r, int _g, int _b, int _a)
    : r(range(_r, 0, 255)), g(range(_g, 0, 255)), b(range(_b, 0, 255)), a(range(_a, 0, 255))
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

bool operator==(const Color& a, const Color& b)
{
    return (a.r == b.r) && (a.g == b.g) && (a.b == b.b) && (a.a == b.a) ? true : false;
}

bool operator!=(const Color& a, const Color& b)
{
    return (a.r == b.r) && (a.g == b.g) && (a.b == b.b) && (a.a == b.a) ? false : true;
}

Color operator+(const Color& a, const Color& b)
{
    return Color(a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a);
}

Color operator-(const Color& a, const Color& b)
{
    return Color(a.r - b.r, a.g - b.g, a.b - b.b);
}

Color operator*(const Color& c, float n)
{
    return Color(c.r * n, c.g * n, c.b * n, c.a * n);
}

Color operator/(const Color& c, float n)
{
    return Color(c.r / n, c.g / n, c.b / n, c.a / n);
}

Color::Color(int rgba)
    : r(range(rgba, 0, 255)), g(range(rgba, 0, 255)), b(range(rgba, 0, 255)), a(range(rgba, 0, 255))
{
    //
}
