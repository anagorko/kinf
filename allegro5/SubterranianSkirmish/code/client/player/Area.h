#ifndef __Area_H__
#define __Area_H__

#include "../../Error.h"
#include "global_math.h"

/// Klasa narzędziowa służąca do określania pozycji (współrzędnych) na planszy
/// dla prostokątnego obiektu (np. bitmapy).

class Area
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
    void reInit(const Area& other);

    // Kostruktor NIE inicjalizujący
    Area();

    // Konstruktor inicjalizujący
    Area(Style s, float a1, float a2, float a3, float a4) throw(Error);

    // Zwraca true jeśli pozycja jest zainicjalizowana
    bool ifInitialized() const  { return initialized; }

    // metody zwracjące współżędne:
    // jeżeli obiekt Area nie został jeszcze zainicjalizowany, rzucają wyjątek
    float x() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Area");
        return _x1;
    }
    float y() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Area");
        return _y1;
    }
    float x1() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Area");
        return _x1;
    }
    float y1() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Area");
        return _y1;
    }
    float x2() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Area");
        return _x2;
    }
    float y2() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Area");
        return _y2;
    }
    float cx() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Area");
        return _x1 + difference(_x1,_x2)/2;
    }
    float cy() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Area");
        return _y1 + difference(_y1,_y2)/2;
    }
    float w() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Area");
        return difference(_x1,_x2);
    }
    float h() const throw(Error)
    {
        if (!initialized) throw Error(__FILE__, __LINE__, "Próba pobrania informacji o niezainicjalizownym obiekcie Area");
        return difference(_y1,_y2);
    }

    // makro zastępujące 4 argumenty wpółżędnymi opisującymi obszar w stylu XYXY
    // przykład:
    /*
        // deklarujemy nasz obszar
        Area my_area;

        // wypełnienie naszego obszaru kolorem czarnym w tradycyjny sposób
        al_draw_filled_rectangle(my_area.x1(), my_Area.y1(), my_Area.x2(), my_Area.y2(), al_map_rgb(0,0,0));

        // wypełnienie naszego obszaru kolorem czarnym z użyciem makra
        al_draw_filled_rectangle(area(my_area), al_map_rgb(0,0,0));
    */
    #define AREA(name_of_area) name_of_area.x1(), name_of_area.y1(), name_of_area.x2(), name_of_area.y2()
    // to samo makro ale z domyślnym name_of_area = area
    #define AREA area.x1(), area.y1(), area.x2(), area.y2()

private:

    bool initialized;

    // współrzędne lewego górnego narożnika
    float _x1, _y1;

    // współrzędne prawego dolnego narożnika
    float _x2, _y2;
};

#endif // __Area_H__
