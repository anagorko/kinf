//
// Szablon gry w Allegro 5. (C) Kółko Informatyczne Szkoły Żagle
//

#ifndef __PLANSZA2D_H__
#define __PLANSZA2D_H__

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
using namespace std;

const float FPS = 60;       // Frames Per Second
bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

void plansza2d_rysuj(ALLEGRO_COLOR p[px][py], int kx, int ky)
{
    for (int x = 0; x < px; x++) {
        for (int y = 0; y < py; y++) {
            al_draw_filled_rectangle(x * kx, y * ky, (x+1) * kx - 1, (y+1)* ky - 1, p[x][y]);
        }
    }
}

int plansza2d_init(int screen_w, int screen_h)
{
    if(!al_init()) {
        cerr << "Błąd podczas inicjalizacji allegro." << endl;
        return -1;
    }
  
    if (!al_init_primitives_addon()) {
        cerr << "Błąd podczas inicjalizacji dodatku 'primitives'." << endl;
        return -1;
    }
    
    if (!al_install_keyboard()) {
        cerr << "Błąd podczas inicjalizacji klawiatury." << endl;
        return -1;
    }

    if (!al_install_mouse()) {
        cerr << "Błąd podczas inicjalizacji myszy." << endl;
        return -1;
    }
  
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        cerr << "Błąd podczas inicjalizacji zegara." << endl;
        return -1;
    }
 
    display = al_create_display(screen_w, screen_h);
    if(!display) {
        cerr << "Błąd podczas inicjalizacji ekranu." << endl;
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        cerr << "Błąd podczas inicjalizacji kolejki zdarzeń." << endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
  
    al_register_event_source(event_queue, al_get_display_event_source(display));  
    al_register_event_source(event_queue, al_get_timer_event_source(timer));  
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));
  
    al_flip_display();  
    al_start_timer(timer);

    return 0;
}

#endif /* __PLANSZA2D_H__ */