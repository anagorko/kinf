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

// UWAGA! nagłówek global.h należy inkludować tylko do plików code/client/player/*.cpp
// ma to na celu uniknięcie upublicznienia poniższych funkcji dla całego projektu

/****************************
    Przyjaźń z Display
****************************/

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
// zwraca true jeśli mysz jest wciśnięta
bool mouse_pressed();
// wywołuje al_set_target_bitmap(display)
void backToDisplay();

/****************************
    Przyjaźń z Player
****************************/

void setGameColor(const Color& color);
Color getGameColor();

/****************************
    Przyjaźń z Font
****************************/

ALLEGRO_FONT* font(int n);

#endif // __GLOBAL_H__

