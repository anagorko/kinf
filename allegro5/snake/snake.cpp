#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
using namespace std;

const float FPS = 60;       // Frames Per Second
const int screen_w = 640;   // szerokość ekranu (screen width)
const int screen_h = 480;   // wysokość ekranu (screen height)
const int segment = 5;      // rozmiar segmentu węża

bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

int init()
{
    if(!al_init()) {
        cerr << "Błąd podczas inicjalizacji allegro." << endl;
        return -1;
    }
  
    if(!al_install_keyboard()) {
        cerr << "Błąd podczas inicjalizacji klawiatury." << endl;
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

/****************************************
 * Tu rozpoczyna się istotna część kodu *
 ****************************************/
 
//
// struktura reprezentująca punkt - parę współrzędnych
//

struct punkt {
    float x;
    float y;
};

//
// struktura reprezentująca węża
//

struct waz {
    struct punkt cielsko[10000];
    struct punkt glowa;
    
    int dlugosc;    // liczba segmentów węża    
};

//
// a oto sam wąż
//

struct waz w;

int main(int argc, char ** argv)
{
    if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }
 
    bool przerysuj = true;
    bool wyjdz = false;
  
    //
    // Tworzymy węża
    //
    
    w.glowa.x = 50;
    w.glowa.y = 50;
    
    w.dlugosc = 100;
    
    for (int i = 0; i < w.dlugosc; i++) {
        w.cielsko[i] = w.glowa;
    }

    //
    // Event loop - główna pętla programu
    //
        
    while(!wyjdz)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            //
            // minęła 1/60 (1/FPS) część sekundy
            //
            przerysuj = true;

            if (key[ALLEGRO_KEY_UP]) {
                w.glowa.y = w.glowa.y - 1;
            }
            if (key[ALLEGRO_KEY_RIGHT]) {
                w.glowa.x = w.glowa.x + 1;
            }
            if (key[ALLEGRO_KEY_DOWN]) {
                w.glowa.y = w.glowa.y + 1;
            }
            if (key[ALLEGRO_KEY_LEFT]) {
                w.glowa.x = w.glowa.x - 1;
            }
            
            //
            // Poniższy kod jest nieefektywny. Kiedyś nauczymy się to robić lepiej.
            //
            
            for (int i = 0; i < w.dlugosc - 1; i++) {
                w.cielsko[i] = w.cielsko[i+1];
            }
            
            w.cielsko[w.dlugosc - 1] = w.glowa;
            
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            key[ev.keyboard.keycode] = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            key[ev.keyboard.keycode] = false;
            
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                wyjdz = true;
            }
        }

        if(przerysuj && al_is_event_queue_empty(event_queue)) {
            przerysuj = false;

            al_clear_to_color(al_map_rgb(0,0,0));
     
            for (int i = 0; i < w.dlugosc; i++) {
                al_draw_filled_rectangle(
                      w.cielsko[i].x * segment, w.cielsko[i].y * segment,
                      (w.cielsko[i].x+1) * segment - 1, (w.cielsko[i].y+1) * segment - 1,
                      al_map_rgb(98,76,54));
            }
             
            al_flip_display();
         }    
    }

    return 0;
}
