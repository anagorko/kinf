#ifndef COLOR_H
#define COLOR_H

#include <allegro_color.h>
#include <string>
#include "../../Error.h"

// Klasa narzędziowa
// opakowanie do ALLEGRO_COLOR

class Color
{
public:

    // konstruktor
    Color(int _r, int _g, int _b, int _a = 255);

    // konstruktory konwertujące
    Color(int* p) throw(Error);

    // operator konwersji do ALLEGRO_COLOR
    operator ALLEGRO_COLOR();

    // zwraca true jeżeli kolor jest ciemny ( (R+G+B) < (255*3) / 2 )
    bool ifDark();

    int getR() const { return r; }
    int getG() const { return g; }
    int getB() const { return b; }
    int getA() const { return a; }

    // kilka mniej lub bardziej przydatnych operatorów
    // inkrementacja zwiększa r, g, oraz b o 1
    //Color operator= {255,0,255,100}
    int& operator[](int i) throw(Error);
    bool operator==(const Color& other);
    bool operator!=(const Color& other);
    Color operator++();
    Color operator++(int);
    Color operator--();
    Color operator--(int);
    Color operator+=(const int& n);
    Color operator-=(const int& n);

    // standardowe kolory
    static Color black();
    static Color white();
    // itd

private:

    // red, green, blue, alfa
    int r, g, b, a;
};

#endif // COLOR_H
