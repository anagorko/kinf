//
// Sztuczne ognie. (C) Kółko Informatyczne Szkoły Żagle
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
using namespace std;

//
// Konfiguracja gry
//

const int screen_w = 1000;   // szerokość ekranu (screen width)
const int screen_h = 562;   // wysokość ekranu (screen height)

/****************************************
 * Tu rozpoczyna się istotna część kodu *
 ****************************************/
 
//
// Struktury danych
//

typedef struct
{
    float x;
    float y;
    
    float dx;
    float dy;
    
    int size;
    int life;
} odlamek;

//
// Zmienne
//

const int default_life = 120;
const int max_n = 1000;
const int fragments = 7;
const float g = 0.01;
int n;

odlamek o[max_n];

//
// Rysowanie planszy
//

void rysuj_plansze()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    
//    al_draw_filled_circle(screen_w/2,screen_h/2, 10, al_map_rgb(255,255,255));
    
    for (int i = 0; i < n; i++) {
        if (o[i].life == 0) continue;

        al_draw_filled_circle(o[i].x, o[i].y, 10, al_map_rgb(10+2*o[i].life, 10+2*o[i].life, 10+2*o[i].life));
    }
}

//
// Mechanika gry
//

void aktualizuj_plansze()
{
    for (int i = 0; i < n; i++) {
        if (o[i].life == 0) continue;
        
        o[i].life--;
        if (o[i].life == 0 && o[i].size > 0) {
            for (int j = 0; j < fragments; j++) {
                o[n].x = o[i].x;
                o[n].y = o[i].y;
                o[n].dx = o[i].dx * (1.0 + (rand() % 100) / 100.0);
                o[n].dy = o[i].dy * (1.0 + (rand() % 100) / 100.0);
                o[n].size = o[i].size - 1;
                o[n].life = default_life;
                
                n++;
            }
        }
        
        o[i].x = o[i].x + o[i].dx;
        o[i].y = o[i].y + o[i].dy;
        
        o[i].dy = o[i].dy + g;
    }
}

//
// Reakcja na akcje graczy
//

void co_robia_gracze()
{
}

//
// Inicjalizacja
//

void inicjalizacja()
{
    n = 0;
    o[n].x = screen_w / 2;
    o[n].y = screen_h - 20;
    o[n].dx = (float) (random() % 100) / 50.0 - 1.0;
    o[n].dy = -2 - (float) (random() % 100) / 100.0;
    o[n].size = 2;
    o[n].life = default_life;
    n++;
}

/****************************************
 * Kod poniżej jest w miarę generyczny  *
 ****************************************/
 
const float FPS = 60;       // Frames Per Second
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

int main(int argc, char ** argv)
{
    if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }
 
    inicjalizacja();
    
    bool przerysuj = true;
    bool wyjdz = false;  

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

            co_robia_gracze();

            aktualizuj_plansze();

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

            rysuj_plansze();

            al_flip_display();
         }    
    }

    return 0;
}
