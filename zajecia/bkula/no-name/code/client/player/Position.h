#ifndef __POSITION_H__
#define __POSITION_H__

#include "../../Error.h"
#include "global.h"

/// Klasa narzędziowa służąca do określania pozycji (współrzędnych) na planszy
/// dla prostokątnego obiektu (np. bitmapy).

class Position
{
public:

    // Różne style określania pozycji
    enum Style {
        XYXY, // opisuje pozycję za pomocą dwóch punktów: lewy górny narożnik i prawy dolney narożnik - styl domyślny
        XYWH, // opisuje pozycję za pomocą punktu lewego górnego narożnika, wysokości i szerokości obiektu
        CXYWH // opisuje pozycję za pomocą punktu przecięcia przekątnych (centrum), wysokości i szerokości
    };

    // Inicjalizuje obiekt za pocą 4 parametrów
    void reInit(Style s, float a1, float a2, float a3, float a4) throw(Error);

    // Inicjalizuje obiekt za pocą innej pozycji, udaje konstruktor kopiujący
    void reInit(const Position& other);

    // Kostruktor NIE inicjalizujący
    Position();

    // Konstruktor inicjalizujący
    Position(Style s, float a1, float a2, float a3, float a4) throw(Error);

    // Zwraca true jeśli pozycja jest zainicjalizowana
    bool ifInitialized() const  { return initialized; }

    // metody zwracjące współżędne:
    // jeżeli obiekt Position nie został jeszcze zainicjalizowany, rzucają wyjątek
    float x() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Position");
        return _x1;
    }
    float y() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Position");
        return _y1;
    }
    float x1() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Position");
        return _x1;
    }
    float y1() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Position");
        return _y1;
    }
    float x2() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Position");
        return _x2;
    }
    float y2() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Position");
        return _y2;
    }
    float cx() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Position");
        return _x1 + difference(_x1,_x2)/2;
    }
    float cy() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Position");
        return _y1 + difference(_y1,_y2)/2;
    }
    float w() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Position");
        return difference(_x1,_x2);
    }
    float h() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Position");
        return difference(_y1,_y2);
    }

    // makro zastępujące 4 argumenty wpółżędnymi opisującymi pozycję w stylu XYXY
    // przykład:
    /*
        // deklarujemy naszą pozycję
        Position my_position;

        // wypełnienie naszej pozycji kolorem czarnym w tradycyjny sposób
        al_draw_filled_rectangle(my_position.x1(), my_position.y1(), my_position.x2(), my_position.y2(), al_map_rgb(0,0,0));

        // wypełnienie naszej pozycji kolorem czarnym z użyciem makra
        al_draw_filled_rectangle(POS(my_position), al_map_rgb(0,0,0));
    */
    #define POS(p) p.x1(), p.y1(), p.x2(), py2()

private:

    bool initialized;

    // współrzędne lewego górnego narożnika
    float _x1, _y1;

    // współrzędne prawego dolnego narożnika
    float _x2, _y2;
};

#endif // __POSITION_H__
