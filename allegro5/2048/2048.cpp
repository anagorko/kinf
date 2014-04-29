
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

string int_to_string(int n) {
    stringstream ss;
    ss << n;
    string s;
    ss >> s;
    return s;
}

class PLANSZA;

class KAFELEK {

    const static int wciecie = 8;
    const static int font_size = 38;

    ALLEGRO_COLOR kolor() {
        if (w == 0) return al_map_rgba(0,0,0,0);
        else if (w == 2) return al_map_rgb_f(1,1,1);
        else if (w == 4) return al_map_rgb_f(1,0.75,0.5);
        else if (w == 8) return al_map_rgb_f(1,0.5,0.25);
        else if (w == 16) return al_map_rgb_f(1,0.6,0.6);
        else if (w == 32) return al_map_rgb_f(1,0.3,0.3);
        else if (w == 64) return al_map_rgb_f(1,0,0);
        else if (w == 128) return al_map_rgb_f(1,1,0);
        else if (w == 256) return al_map_rgb_f(0.85,0.75,0.1);
        else if (w == 512) return al_map_rgb_f(0.7,0.5,0.2);
        else if (w == 1024) return al_map_rgb_f(0.8,0,0.8);
        else if (w == 2048) return al_map_rgb_f(0.2,0.2,1);
        else return al_map_rgb_f(0.2,0.2,0.2);
    }

    int x, y;

public:

    const static int bok = 100;

    int init(int a, int b) {
        x = a;
        y = b;
    }

    long long w; // wartość

    void rysuj() {

        al_draw_filled_rounded_rectangle(x, y, x+bok, y+bok, wciecie, wciecie, kolor());
        if (w != 0) al_draw_text(font[font_size], al_map_rgb(0,0,0), x+bok/2, y-font_size/2+bok/2, ALLEGRO_ALIGN_CENTRE, int_to_string(w).c_str());
        al_draw_rounded_rectangle(x, y, x+bok, y+bok, wciecie, wciecie, al_map_rgb(0,0,0), 2);
    }

    void animacja() {
        for (int czas = 0, mniej = bok/4; mniej > 0; mniej-=6) {
            al_draw_filled_rounded_rectangle(x+mniej, y+mniej, x+bok-mniej, y+bok-mniej, wciecie, wciecie, kolor());
            al_flip_display();
            usleep(100000/(bok/4));
        }
    }
};

class MENU {
    void nowa_gra() { /* init() */ }
    void cofnij();
public:
    void rysuj();
    void aktualizuj();
};

class WYNIKI {

    long long wynik;
    long long rekord;

public:

    void init() {
        wynik = 0;
    }

    void rysuj();

    void zwieksz_wynik(int pkt, double czas) {
        wynik += pkt * czas;
    }
};

class PLANSZA {

    static const short SIZE = 4;
    static const int pomiedzy = 10;

    KAFELEK tab[SIZE][SIZE];

    void dodaj_kafelek() {
        short x = random()%4;
        short y = random()%4;
        if (tab[x][y].w == 0) {
            if (random()%8 == 0) tab[x][y].w = 4;
            else tab[x][y].w = 2;
            tab[x][y].animacja();
        } else dodaj_kafelek();
    }

    bool przegrana() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (tab[i][j].w == 0) return false;
            }
        }
        return true;
    }

    void podsun(KAFELEK * k[SIZE]) {
        vector <int> v;
        for (int i = 0; i < SIZE; i++) {
            if (k[i]->w != 0) {
                v.push_back(k[i]->w);
                k[i]->w = 0;
            }
        }
        for (int i = 0; i < v.size(); i++) {
            k[i]->w = v[i];
        }
    }

    void polacz(KAFELEK * k[SIZE]) {
        for (int i = 0; i < SIZE-1; i++) {
            if (k[i]->w == k[i+1]->w) {
                k[i]->w *= 2;
                k[i+1]->w = 0;
            }
        }
    }

public:

    void init() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                tab[i][j].w = 0;
                tab[i][j].init(
                    SCREEN_W/2 -2*KAFELEK::bok -2.5*pomiedzy +i*(KAFELEK::bok+pomiedzy),
                    SCREEN_H/2 -2*KAFELEK::bok -2.5*pomiedzy +j*(KAFELEK::bok+pomiedzy)
                );
            }
        }
        dodaj_kafelek();
        dodaj_kafelek();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if(tab[i][j].w == 4) {
                    dodaj_kafelek();
                    return;
                }
            }
        }
    }

    void rysuj() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                tab[i][j].rysuj();
            }
        }
    }

    int pkt;

    void ruch(KIERUNEK k) {

        pkt = 0;

        if (k == N) {
            for (int x = 0; x < SIZE; x++) {
                KAFELEK * k[SIZE];
                for (int y = 0; y < SIZE; y++) {
                    k[y] = &tab[x][y];
                }
                podsun(k);
                polacz(k);
                podsun(k);
            }
        } else if (k == S) {
            for (int x = 0; x < SIZE; x++) {
                KAFELEK * k[SIZE];
                for (int y = 0; y < SIZE; y++) {
                    k[y] = &tab[x][SIZE-1-y];
                }
                podsun(k);
                polacz(k);
                podsun(k);
            }
        } else if (k == W) {
            for (int y = 0; y < SIZE; y++) {
                KAFELEK * k[SIZE];
                for (int x = 0; x < SIZE; x++) {
                    k[x] = &tab[x][y];
                }
                podsun(k);
                polacz(k);
                podsun(k);
            }
        } else if (k == E) {
            for (int y = 0; y < SIZE; y++) {
                KAFELEK * k[SIZE];
                for (int x = 0; x < SIZE; x++) {
                    k[x] = &tab[SIZE-1-x][y];
                }
                podsun(k);
                polacz(k);
                podsun(k);
            }
        }

        if (przegrana()) wyjdz = true;
        else dodaj_kafelek();
    }
};

class STEROWANIE {

    bool ruszony;
    bool zeruj_czas;

public:

    void init() {
        czas = 0;
        ruszony = false;
        zeruj_czas = true;
    }

    double czas;

    KIERUNEK ruch() {

        if (zeruj_czas) czas = 0;
        czas += 1-czas;
        zeruj_czas = true;

        if (key[ALLEGRO_KEY_UP]) {
            if (!ruszony) {
                ruszony = true;
                return N;
            }
        } else if (key[ALLEGRO_KEY_RIGHT]) {
            if (!ruszony) {
                ruszony = true;
                return E;
            }
        } else if (key[ALLEGRO_KEY_DOWN]) {
            if (!ruszony) {
                ruszony = true;
                return S;
            }
        } else if (key[ALLEGRO_KEY_LEFT]) {
            if (!ruszony) {
                ruszony = true;
                return W;
            }
        } else {
            ruszony = false;
        }

        zeruj_czas = false;
        return brak;
    }
};

class GRA {

    float FPS;

    ALLEGRO_DISPLAY_MODE disp_data;
    ALLEGRO_DISPLAY * display;
    ALLEGRO_EVENT_QUEUE * event_queue;
    ALLEGRO_TIMER * timer;

    PLANSZA plansza;
    STEROWANIE sterowanie;
    WYNIKI wyniki;
    MENU menu;

    void inicjalizuj_obiekty() {
        wyniki.init();
        sterowanie.init();
        plansza.init();
    }

    void aktualizuj_obiekty() {
        KIERUNEK k;
        k = sterowanie.ruch();
        if (k != brak) {
            plansza.ruch(k);
            wyniki.zwieksz_wynik(plansza.pkt, sterowanie.czas);
        }
    }

    void rysuj_obiekty() {
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
            font.push_back(al_load_ttf_font("FreeMono.ttf",i,0));
            if (!font[font.size()-1]) {
                cerr << "Nie mogę załadować czcionki FreeMono.ttf" << endl;
                al_destroy_display(display);
                al_destroy_timer(timer);
                return -1;
            }
        }
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
        al_get_display_mode(0, &disp_data);
        SCREEN_W = disp_data.width;
        SCREEN_H = disp_data.height;

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

        if (!init()) wyjdz == true;

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

                al_clear_to_color(al_map_rgb(235,220,205));
                rysuj_obiekty();
                al_flip_display();
            }
        }
    }
};

int main() {
    srandom(time(NULL)+getpid());
    GRA gra;
    gra.run();
}
