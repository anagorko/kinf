

#include <iostream>
#include <vector>
#include <sstream>

#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

bool wyjdz = false;

int SCREEN_W;
int SCREEN_H;

bool key[ALLEGRO_KEY_MAX];
int mouse_x;
int mouse_y;
bool mouse_pressed = false;

enum KIERUNEK {brak = 0, N, E, S, W};

vector <ALLEGRO_FONT*> font;

class Plansza
{
public:

    int pola[3][3];

    int w;

    int ktore_klikniecie;

    Plansza()
    {
        w = 100;
        ktore_klikniecie = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                pola[i][j] = 0;
            }
        }
    }

    void rysuj()
    {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int x = i * w + SCREEN_W/2 - (w * 3) / 2;
                int y = j * w + SCREEN_H/2 - (w * 3) / 2;
                al_draw_rectangle(x, y, x + w, y + w, al_map_rgb(255,255,255), 3);
                if (pola[i][j] == 1) {
                    al_draw_circle(x + w/2, y + w/2, w/3, al_map_rgb(0,255,0), w/10);
                } else if (pola[i][j] == 2) {
                    al_draw_line(x + w/5, y + w/5, x + w - w/5, y + w - w/5, al_map_rgb(255,0,0), w/10);
                    al_draw_line(x + w - w/5, y + w/5, x + w/5, y + w - w/5, al_map_rgb(255,0,0), w/10);
                }
            }
        }
    }

    void aktualizuj()
    {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int x = i * w + SCREEN_W/2 - (w * 3) / 2;
                int y = j * w + SCREEN_H/2 - (w * 3) / 2;
                if (mouse_pressed && pola[i][j] == 0 && mouse_x < x+w && mouse_x > x && mouse_y < y+w && mouse_y > y) {
                    ktore_klikniecie++;
                    if ((ktore_klikniecie % 2) == 1) pola[i][j] = 1;
                    else if ((ktore_klikniecie % 2) == 0) pola[i][j] = 2;
                }
            }
        }
    }
};

class GRA {

    float FPS;

    ALLEGRO_DISPLAY_MODE disp_data;
    ALLEGRO_DISPLAY * display;
    ALLEGRO_EVENT_QUEUE * event_queue;
    ALLEGRO_TIMER * timer;

    Plansza plansza;

    void inicjalizuj_obiekty() {
        //
    }

    void aktualizuj_obiekty() {
        plansza.aktualizuj();
    }

    void rysuj_obiekty() {
        al_clear_to_color(al_map_rgb(170,0,170));
        plansza.rysuj();
    }

    int init() {

        if (!al_init()) {
            cout << "Błąd podczas inicjalizacji allegro." << endl;
            return -1;
        }

        if (!al_init_primitives_addon()) {
            cout << "Błąd podczas inicjalizacji dodatku 'primitives'." << endl;
            return -1;
        }

        if (!al_install_keyboard()) {
            cout << "Błąd podczas inicjalizacji klawiatury." << endl;
            return -1;
        }

        if (!al_install_mouse()) {
            cout << "Błąd podczas inicjalizacji myszy." << endl;
            return -1;
        }

        al_init_image_addon();
        al_init_font_addon();
        al_init_ttf_addon();

        for (int i = 0; i < 75; i++) {
            font.push_back(al_load_ttf_font("Arial.ttf",i,0));
            if (!font[font.size()-1]) {
                cerr << "Nie mogę załadować czcionki FreeMono.ttf" << endl;
                al_destroy_display(display);
                al_destroy_timer(timer);
                return -1;
            }
        }
        al_set_new_display_flags(ALLEGRO_WINDOWED);
        al_get_display_mode(0, &disp_data);
        SCREEN_W = disp_data.width;
        SCREEN_H = disp_data.height;

        SCREEN_W = 800;
        SCREEN_H = 500;

        display = al_create_display(SCREEN_W, SCREEN_H);
        if(!display) {
            cout << "Błąd podczas inicjalizacji ekranu." << endl;
            al_destroy_timer(timer);
            return -1;
        }

        timer = al_create_timer(1.0 / FPS);
        if (!timer) {
            cout << "Błąd podczas inicjalizacji zegara." << endl;
            return -1;
        }

        event_queue = al_create_event_queue();
        if(!event_queue) {
            cout << "Błąd podczas inicjalizacji kolejki zdarzeń." << endl;
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

public:

    GRA() {
        FPS = 60;
    }

    void run() {

        if (init() != 0) wyjdz = true;

        bool przerysuj = true;

        while (wyjdz != true) {

            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);

            if(ev.type == ALLEGRO_EVENT_TIMER) {

                przerysuj = true;

                aktualizuj_obiekty();

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

            if (przerysuj && al_is_event_queue_empty(event_queue)) {
                przerysuj = false;

                rysuj_obiekty();
                al_flip_display();
            }
        }
    }
};

int main(int, char**) {
    srandom(time(NULL)+getpid());
    GRA gra;
    gra.run();
}
