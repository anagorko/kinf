#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <algorithm>

#include "Color.h"
#include "Font.h"
#include "../../Error.h"

#include <allegro5.h>
#include <allegro_image.h>
#include <allegro_primitives.h>

/// Zbiór funkcji globalnych TYLKO dla wątku player

/// UWAGA! nagłówek global.h należy inkludować tylko do plików code/client/player/*.cpp
/// ma to na celu uniknięcie upublicznienia poniższych funkcji dla całego programu

/// Przyjaźń z Display

// zwarca szerokość ekranu
int screen_w();
// zwraca wysokość ekrau
int screen_h();
// zwraca true jeśli klawisz n jest wciśnięty
bool key(int n) throw(Error);
// zwraca x myszy
int mouse_x();
// zwraca y myszy
int mouse_y();
// zwraca true jeśli LPM jest wciśnięty
bool mouse_pressed();
// wywołuje al_set_target_bitmap(display)
void backToDisplay();

/// Przyjaźń z Player

void setGameColor(const Color& color);
Color getGameColor();

/// Przyjaźń z Font

ALLEGRO_FONT* font(int n);

/// Pomocne funkcje

template<typename T> T difference(T a, T b)
{
    return a > b ? a-b : b-a;
}

template<typename T> T max3(T a, T b, T c)
{
    return max(max(a,b),c);
}

#endif // __GLOBAL_H__
