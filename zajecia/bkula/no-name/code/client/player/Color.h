#ifndef __COLOR_H__
#define __COLOR_H__

#include <allegro_color.h>
#include <string>
#include "../../Error.h"

// Klasa narzędziowa
// opakowanie do ALLEGRO_COLOR

class Color
{
public:

    // konstruktory
    Color(int _r, int _g, int _b, int _a = 255);
    explicit Color(int* p) throw(Error);

    // konstruktory konwertujące
    Color(int rgba);

    // operator konwersji do ALLEGRO_COLOR
    operator ALLEGRO_COLOR();

    // zwraca true jeżeli kolor jest ciemny ( (r+g+b) < (255*3) / 2 )
    bool ifDark();

    int getR() const { return r; }
    int getG() const { return g; }
    int getB() const { return b; }
    int getA() const { return a; }

    // kilka mniej lub bardziej przydatnych operatorów
    // np. inkrementacja zwiększa r, g, oraz b o 1
    int& operator[](int i) throw(Error);
    Color operator++();
    Color operator++(int);
    Color operator--();
    Color operator--(int);
    Color operator+=(const int& n);
    Color operator-=(const int& n);
    friend bool operator!=(const Color& a, const Color& b);
    friend bool operator==(const Color& a, const Color& b);
    friend Color operator+(const Color& a, const Color& b);
    friend Color operator-(const Color& a, const Color& b);
    friend Color operator*(const Color& c, float n);
    friend Color operator/(const Color& c, float n);

    // standardowe kolory
    static Color null();
    static Color black();
    static Color white();
    static Color red();
    static Color green();
    static Color blue();
    static Color yellow();
    static Color orange();
    static Color pink();
    static Color grey();
    static Color purple();
    static Color brown();
    // itd

private:

    // red, green, blue, alfa
    int r, g, b, a;
};

#endif // __COLOR_H__
