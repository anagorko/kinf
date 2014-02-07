//
// Gra w kolory (C) Benedykt Kula, na podstawie:
// Szablon gry w Allegro 5. (C) Kółko Informatyczne Szkoły Żagle
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <sstream>
using namespace std;

//
// Konfiguracja gry
//

int screen_w;   // szerokość ekranu (screen width)
int screen_h;   // wysokość ekranu (screen height)

/****************************************
 * Tu rozpoczyna się istotna część kodu *
 ****************************************/

//
// Struktury danych
//

//
// Zmienne
//

//
// Rysowanie planszy
//

double R, G, B;
double r = 1.1;
double g = 1.2;
double b = 1.3;
int z = 0;
bool r_czy_spada = false, g_czy_spada = false, b_czy_spada = false;

void podaj_kolor_tla() {
    R = 0;
    G = 0;
    B = 0;
}

void rysuj_plansze()
{
    if (r_czy_spada) R -= r;
    else R += r;

    if (g_czy_spada) G -= g;
    else G += g;

    if (b_czy_spada) B -= b;
    else B += b;

	//z++;
	r = r*1.001;
	g = g*1.001;
	b = b*1.001;
	z = 0;

    if (R <= 0) {
        r_czy_spada = false;
        R = 0;
    }
    if (G <= 0) {
        g_czy_spada = 0;
        G = 0;
    }
    if (B <= 0) {
        b_czy_spada = false;
        B = 0;
    }

    if (R >= 255) {
        r_czy_spada = true;
        R = 255;
    }
    if (G >= 255) {
        g_czy_spada = 1;
        G = 255;
    }
    if (B >= 255) {
        b_czy_spada = 1;
        B = 255;
    }

    al_clear_to_color(al_map_rgb(R,G,B));

    ALLEGRO_COLOR kolor_czcionki = al_map_rgb (255-(R), 255-(G), 255-(B));

    al_draw_filled_rectangle (50, 50, 50+R, 70, al_map_rgb(255,0,0));
    //al_draw_text (font, kolor_czcionki, 50+R+15, 50+10, ALLEGRO_ALIGN_RIGHT, intostring(R).c_str());

    al_draw_filled_rectangle (50, 90, 50+G, 110, al_map_rgb(0,255,0));
    //al_draw_text (font, kolor_czcionki, 50+G+15, 90+10, ALLEGRO_ALIGN_RIGHT, intostring(G).c_str());

    al_draw_filled_rectangle (50, 130, 50+B, 150, al_map_rgb(0,0,255));
    //al_draw_text (font, kolor_czcionki, 50+B+15, 130+10, ALLEGRO_ALIGN_RIGHT, intostring(B).c_str());
}

//
// Mechanika gry
//

void aktualizuj_plansze()
{
}

//
// Reakcja na akcje graczy
//

void co_robia_gracze()
{
}

/****************************************
 * Kod poniżej jest w miarę generyczny  *
 ****************************************/

const float FPS = 60;       // Frames Per Second
bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

ALLEGRO_DISPLAY_MODE disp_data;

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

    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    al_get_display_mode(0, &disp_data);
    screen_w = disp_data.width;
    screen_h = disp_data.height;

    display = al_create_display(screen_w, screen_h);
    if(!display) {
        cerr << "Błąd podczas inicjalizacji ekranu." << endl;
        al_destroy_timer(timer);
        return -1;
    }

    al_set_window_title(display, "Dupa wołowa");

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
    podaj_kolor_tla();

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
        }

        if(przerysuj && al_is_event_queue_empty(event_queue)) {
            przerysuj = false;

            rysuj_plansze();

            al_flip_display();
         }
    }

    return 0;
}
