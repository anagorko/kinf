//
// Klon gry Flappy Bird. (C) Kółko Informatyczne Szkoły Żagle
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
using namespace std;

bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze

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

struct przeszkoda {
    int x, y;
    
    const int gap = 100;
};

struct ptaszek {
    float x, y;
};

//
// Zmienne
//

const int ile_przeszkod = 4;

struct przeszkoda p[ile_przeszkod];
struct ptaszek pt;
float v;

//
// Inicjalizacja
//

void inicjalizacja()
{
    for (int i = 0; i < ile_przeszkod; i++) {
        p[i].x = i * screen_w / ile_przeszkod;
        p[i].y = random() % (screen_h - 60);
    }
    
    pt.x = screen_w / 4;
    pt.y = screen_h / 2;
    
    v = 0;
}

//
// Rysowanie planszy
//

void rysuj_plansze()
{
    al_clear_to_color(al_map_rgb(255,255,255));

    for (int i = 0; i < ile_przeszkod; i++) {
        al_draw_filled_rectangle(p[i].x, 0, p[i].x + 60, screen_h, al_map_rgb(0,0,255));
        al_draw_filled_rectangle(p[i].x, p[i].y, p[i].x + 60, p[i].y + 200, al_map_rgb(255,255,255));
    }
    
    al_draw_filled_circle(pt.x, pt.y, 20, al_map_rgb(255,0,0));
}

//
// Mechanika gry
//

void aktualizuj_plansze()
{
    for (int i = 0; i < ile_przeszkod; i++) {
        p[i].x = p[i].x - 2;
        if (p[i].x < 0) { 
            p[i].x = screen_w;
        }
    }
    
    v += 1;
    
    pt.y += v;
    
    if (pt.y > screen_h) {
        v = -12;
    }
}

//
// Reakcja na akcje graczy
//

void co_robia_gracze()
{
    if (key[ALLEGRO_KEY_SPACE]) {
        v = -10;
    }
    
}

/****************************************
 * Kod poniżej jest w miarę generyczny  *
 ****************************************/
 
const float FPS = 60;       // Frames Per Second

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
 
    bool przerysuj = true;
    bool wyjdz = false;  

    //
    // Event loop - główna pętla programu
    //
    
    inicjalizacja();
    
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
