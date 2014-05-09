//
// Szablon gry w Allegro 5. (C) Kółko Informatyczne Szkoły Żagle
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cmath>

using namespace std;

//
// Konfiguracja gry
//

ALLEGRO_DISPLAY_MODE disp_data;
int screen_w = 1000;   // szerokość ekranu (screen width)
int screen_h = 562;   // wysokość ekranu (screen height)

bool key[ALLEGRO_KEY_MAX];
int mouse_x, mouse_y;
bool mouse_pressed;

/****************************************
 * Tu rozpoczyna się istotna część kodu *
 ****************************************/

//
// Struktury danych
//

class ruchomy_obiekt {

    float speed;
    float x, y;
    float r;
    float cel_x, cel_y;

public:

    void init() {
        r = 20;
        speed = 2.5;
        x = screen_w/2;
        y = screen_h/2;
        cel_x = x;
        cel_y = y;
    }

    void draw() {
        al_draw_line (cel_x-8,cel_y-8,cel_x+8,cel_y+8,al_map_rgb(128,0,0),3);
        al_draw_line (cel_x+8,cel_y-8,cel_x-8,cel_y+8,al_map_rgb(128,0,0),3);
        al_draw_filled_circle (x, y, r, al_map_rgb(128,0,128));
    }

    void ustaw_cel(float a, float b) {
        cel_x = a, cel_y = b;
    }

    void ruch() {

        float odleglosc_x = cel_x-x;
        float odleglosc_y = cel_y-y;

        if (x!=cel_x) x += odleglosc_x/abs(odleglosc_x) * speed * (pow(odleglosc_x,2) / (pow(odleglosc_x,2) + pow(odleglosc_y,2)));
        if (y!=cel_y) y += odleglosc_y/abs(odleglosc_y) * speed * (pow(odleglosc_y,2) / (pow(odleglosc_x,2) + pow(odleglosc_y,2)));
    }
};

ruchomy_obiekt * kolo = new ruchomy_obiekt;

//
// Zmienne
//

void inicjalizuj_obiekty() {
    kolo->init();
}

//
// Rysowanie planszy
//

void rysuj_plansze()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    kolo->draw();
}

//
// Mechanika gry
//

void aktualizuj_plansze()
{
    kolo->ruch();
}

//
// Reakcja na akcje graczy
//

void co_robia_gracze()
{
    if (mouse_pressed) kolo->ustaw_cel(mouse_x,mouse_y);
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

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_get_display_mode(0, &disp_data);
    screen_w = disp_data.width;
    screen_h = disp_data.height;

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

    inicjalizuj_obiekty();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
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
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            wyjdz = true;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            mouse_x = ev.mouse.x;
            mouse_y = ev.mouse.y;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mouse_pressed = false;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mouse_pressed = true;
        }

        if(przerysuj && al_is_event_queue_empty(event_queue)) {
            przerysuj = false;

            rysuj_plansze();

            al_flip_display();
         }
    }

    return 0;
}
