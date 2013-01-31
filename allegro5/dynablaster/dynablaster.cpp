//
// Klon gry DynaBlaster. (C) Kółko Informatyczne Szkoły Żagle
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"

#include <iostream>
using namespace std;

//
// Konfiguracja gry
//

const int sz = 13;
const int wy = 13;

const int k_sz = 35;
const int k_wy = 35;

const float FPS = 60;       // Frames Per Second

const int screen_w = sz*k_sz;   // szerokość ekranu (screen width)
const int screen_h = wy*k_wy;    // wysokość ekranu (screen height)

const int energia_ruchu = 7;
const int dlugosc_lontu = 70;
const int czas_wybuchu = 14;

bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze
 
bool wyjdz = false;
bool wybuchl[2];

/********************************************************************************
 * Tu rozpoczyna się istotna część kodu                                         *
 ********************************************************************************/
 
//
// Struktury danych
//

enum typ_kafelka
{ 
    pusty = 0,
    
    // kafelki - poziom podłogi
    
    zwykla_podloga,

    // kafelki - ściany
    
    niezniszczalna, zwykla,

    // kafelki - obiekty
    
    gracz, bomba, bonus_bomba, bonus_zasieg, 

    // kafelki - wybuchy
    
    wybuch,
    
    // potrzebne do deklaracji tablicy poniżej
    
    liczba_kafelkow
};

struct kafelek
{
    enum typ_kafelka typ;
    
    int wariant;
    
    // pole wykorzystywane przez bomby
    int kto; // wykorzystujemy to pole, by pamiętać, który gracz postawił bombę
    // pole wykorzystywane przez bomby i wybuch
    int dl; // ile pozostało jeszcze czasu do wybuchu / do wypalenia
};

const string plik_z_kafelkiem[liczba_kafelkow] =
{
    "kafelki/pusty.png", // pusty
    "kafelki/pavement.png", // zwykla_podloga
    "kafelki/sciana_niezniszczalna.png", // ściana niezniszczalna
    "kafelki/sciana.png", // ściana zwykla
    "kafelki/gracz.png", // gracz
    "kafelki/bomba.png", // bomba
    "kafelki/bonus_bomba.png", // bonus_bomba
    "kafelki/bonus_zasieg.png", // bonus_zasieg
    "kafelki/wybuch.png"  // wybuch
};

struct gracz
{
    int x, y; // pozycja na planszy
    
    int kolor; // 0 lub 1, wybiera wariant kafelka "gracz"
    int wariant; // kierunek ruchu
        
    int energia;
    
    int ile_bomb;
    int zasieg_wybuchu;
    
    bool moze_stawiac;
};

struct plansza
{
    struct kafelek podloga[sz][wy];
    struct kafelek sciana[sz][wy];
    struct kafelek obiekt[sz][wy];
    struct kafelek wybuch[sz][wy];

    struct gracz g[2];
};

//
// Zmienne
//

struct plansza p;

ALLEGRO_BITMAP* bitmapa[liczba_kafelkow];

//
// Inicjalizacja
//

bool przygotuj_bitmapy()
{
    for (int i = 0; i < liczba_kafelkow; i++) {
        bitmapa[i] = al_load_bitmap(plik_z_kafelkiem[i].c_str());
        
        if (!bitmapa[i]) {
            cerr << "Błąd podczas wczytywania bitmapy " << plik_z_kafelkiem[i] << "." << endl;
            return false;
        }
    }
    
    return true;
}

void przygotuj_plansze()
{
    //
    // jeszcze nikt nie wybuchł...
    //
    for (int i = 0; i < 2; i++) {
        wybuchl[i] = false;
    }
    
    // 
    // poziom podłogi
    //
    
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < wy; j++) {
            p.podloga[i][j].typ = zwykla_podloga;
            p.podloga[i][j].wariant = random() % 4; // mamy 4 warianty podłogi
        }
    }

    // 
    // czyścimy poziom planszy
    //

    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < wy; j++) {
            p.sciana[i][j].typ = pusty;
            p.sciana[i][j].wariant = 0;
        }
    }

    //
    // rozrzucamy losowo rumowisko
    //
    
    for (int i = 0; i < sz*wy*3/4; i++) {
        p.sciana[random() % sz][random() % wy].typ = zwykla;
    }
    
    //
    // obok graczy musi być pusta przestrzeń
    //
    
    p.sciana[1][1].typ = pusty;
    p.sciana[2][1].typ = pusty;
    p.sciana[1][2].typ = pusty;

    p.sciana[sz-2][wy-2].typ = pusty;
    p.sciana[sz-3][wy-2].typ = pusty;
    p.sciana[sz-2][wy-3].typ = pusty;
    
    //
    // plansza otoczona jest niezniszczalnymi ścianami
    //
    
    for (int i = 0; i < sz; i++) {
        p.sciana[i][0].typ = niezniszczalna;
        p.sciana[i][0].wariant = 0;
        
        p.sciana[i][wy-1].typ = niezniszczalna;
        p.sciana[i][wy-1].wariant = 0;        
    }

    for (int i = 0; i < wy; i++) {
        p.sciana[0][i].typ = niezniszczalna;
        p.sciana[0][i].wariant = 0;
        
        p.sciana[sz-1][i].typ = niezniszczalna;
        p.sciana[sz-1][i].wariant = 0;        
    }

    // 
    // niezniszczalne kolumny
    //
    
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < wy; j++) {
            if ((i % 2 == 0) && (j % 2 == 0)) {
                p.sciana[i][j].typ = niezniszczalna;
                p.sciana[i][j].wariant = 0;
            }
        }
    }

    //
    // rozstawiamy bonusy
    //

    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < wy; j++) {
            p.obiekt[i][j].typ = pusty;
            p.obiekt[i][j].wariant = 0;

            if (p.sciana[i][j].typ == zwykla) {
                switch (random() % 10) {
                case 0:
                    p.obiekt[i][j].typ = bonus_bomba;
                    p.obiekt[i][j].wariant = 0;
                    p.obiekt[i][j].dl = (czas_wybuchu*3)/2;
                    break;
                case 1:
                    p.obiekt[i][j].typ = bonus_zasieg;
                    p.obiekt[i][j].wariant = 0;
                    p.obiekt[i][j].dl = (czas_wybuchu*3)/2;
                    break;
                }
            }
        }
    }
        
    //
    // rozstawiamy graczy
    //
    
    p.g[0].x = sz - 2; p.g[0].y = wy - 2; // prawy dolny róg
    p.g[0].kolor = 0;
    p.g[0].wariant = 0;
    p.g[0].energia = 100; // zaczynamy gotowi do działania :)
    p.g[0].ile_bomb = 1;
    p.g[0].zasieg_wybuchu = 1;
    p.g[0].moze_stawiac = true;
    
    p.g[1].x = 1; p.g[1].y = 1; // lewy górny róg
    p.g[1].kolor = 1;
    p.g[1].wariant = 0;
    p.g[1].energia = 100;
    p.g[1].ile_bomb = 1;
    p.g[1].zasieg_wybuchu = 1;
    p.g[1].moze_stawiac = true;
}

//
// Rysowanie planszy
//

void rysuj_plansze()
{
    al_clear_to_color(al_map_rgb(0,0,0));
        
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < wy; j++) {
            // najpierw podłoga
            al_draw_bitmap_region(bitmapa[p.podloga[i][j].typ], p.podloga[i][j].wariant*k_sz, 
                                  0, k_sz, k_wy, i*k_sz, j*k_sz, 0);

            // potem obiekty
            al_draw_bitmap_region(bitmapa[p.obiekt[i][j].typ], p.obiekt[i][j].wariant*k_sz, 
                                  0, k_sz, k_wy, i*k_sz, j*k_sz, 0);
            
            // później ściany - mogą przykrywać obiekty
            al_draw_bitmap_region(bitmapa[p.sciana[i][j].typ], p.sciana[i][j].wariant*k_sz, 
                                  0, k_sz, k_wy, i*k_sz, j*k_sz, 0);
            
            // teraz gracze
            
            for (int k = 0; k < 2; k++) {
                if (p.g[k].x == i && p.g[k].y == j) {
                    // k-ty gracz stoi na polu (i,j)
                    
                    al_draw_bitmap_region(bitmapa[gracz], (p.g[k].kolor * 4 + p.g[k].wariant) * k_sz,
                                          0, k_sz, k_wy, i*k_sz, j*k_sz, 0);
                }
            }
            
            // na końcu wybuchy
            al_draw_bitmap_region(bitmapa[p.wybuch[i][j].typ], p.wybuch[i][j].wariant*k_sz, 
                                  0, k_sz, k_wy, i*k_sz, j*k_sz, 0);
        }
    }
    
    //
    // wyświetlamy zasięg i ilość bomb każdego z graczy
    //
    
    for (int i = 0; i < 2; i++) {
        int x;
        
        if (i == 0) {
            x = sz - 1;
        } else {
            x = 0;
        }
        
        for (int j = 0; j < p.g[i].ile_bomb; j++) {
            al_draw_bitmap_region(bitmapa[bomba], 0, 
                                  0, k_sz, k_wy, x*k_sz, j*k_sz, 0);
        }

        for (int j = 0; j < p.g[i].zasieg_wybuchu; j++) {
            al_draw_bitmap_region(bitmapa[wybuch], 0, 
                                  0, k_sz, k_wy, x*k_sz, (wy-1-j)*k_sz, 0);
        }
    }
}

//
// Mechanika gry
//

void aktualizuj_plansze()
{
    //
    // 
    //
    
    for (int i = 0; i < 2; i++) {
        if (p.obiekt[p.g[i].x][p.g[i].y].typ == bonus_bomba) {
            p.g[i].ile_bomb++;
            p.obiekt[p.g[i].x][p.g[i].y].typ = pusty;
            p.obiekt[p.g[i].x][p.g[i].y].dl = 0;
        }
        if (p.obiekt[p.g[i].x][p.g[i].y].typ == bonus_zasieg) {
            p.g[i].zasieg_wybuchu++;
            p.obiekt[p.g[i].x][p.g[i].y].typ = pusty;
            p.obiekt[p.g[i].x][p.g[i].y].dl = 0;
        }
    }
    
    //
    // skanujemy planszę w poszukiwaniu wybuchów
    //
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < wy; j++) {
            if (p.wybuch[i][j].typ == wybuch) {
                p.wybuch[i][j].dl--;
                if (p.wybuch[i][j].dl % 3 == 0) {
                    p.wybuch[i][j].wariant = (p.wybuch[i][j].wariant + 1) % 2;
                }
                            
                if (p.obiekt[i][j].typ == bomba) {
                    // bomba wybucha od razu
                    
                    p.obiekt[i][j].dl = 0;
                }
                
                if (p.wybuch[i][j].dl == 0) {
                    p.wybuch[i][j].typ = pusty;
                } else {
                    if (p.g[0].x == i && p.g[0].y == j) {
                        wyjdz = true;
                        wybuchl[0] = true;
                    }
                    if (p.g[1].x == i && p.g[1].y == j) {
                        wyjdz = true;
                        wybuchl[1] = true;
                    }
                    
                    if (p.obiekt[i][j].typ == bonus_bomba ||
                        p.obiekt[i][j].typ == bonus_zasieg) {
                        p.obiekt[i][j].dl--;
                        
                        if (p.obiekt[i][j].dl <= 0) {
                            p.obiekt[i][j].typ = pusty;
                            p.obiekt[i][j].dl = 0;
                        }
                    }
                    
                }
            }
        }
    }

    //
    // skanujemy planszę w poszukiwaniu bomb
    //
    
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < wy; j++) {
            if (p.obiekt[i][j].typ == bomba) {
                //  na polu (i,j) stoi bomba
                
                p.obiekt[i][j].dl--;
                
                if (p.obiekt[i][j].dl <= 0) {
                    // bomba wybuchła
                    
                    // czyja to bomba?
                    int kto = p.obiekt[i][j].kto;

                    // usuwamy ją z planszy
                    p.obiekt[i][j].typ = pusty;
                    p.obiekt[i][j].wariant = 0;
                    
                    // gracz może ją znów stawiać
                    p.g[kto].ile_bomb++;
                    
                    int z = p.g[kto].zasieg_wybuchu;
                    int k;
                                    
                    // propagacja wybuchu w górę
                    k = 0;
                    while (k <= z) {
                        if (p.sciana[i][j-k].typ == pusty) {
                            // puste pole
                            p.wybuch[i][j-k].typ = wybuch;
                            p.wybuch[i][j-k].dl = czas_wybuchu;
                        } else if (p.sciana[i][j-k].typ == zwykla) {
                            // sciana zwykła
                            p.wybuch[i][j-k].typ = wybuch;
                            p.wybuch[i][j-k].dl = czas_wybuchu;
                            
                            // jest niszczona przez wybuch
                            p.sciana[i][j-k].typ = pusty;
                            
                            break;
                        } else {
                            // sciana niezniszczalna
                            break;
                        }
                        k++;
                    }


                    // propagacja wybuchu w dół
                    k = 0;
                    while (k <= z) {
                        if (p.sciana[i][j+k].typ == pusty) {
                            // puste pole
                            p.wybuch[i][j+k].typ = wybuch;
                            p.wybuch[i][j+k].dl = czas_wybuchu;
                        } else if (p.sciana[i][j+k].typ == zwykla) {
                            // sciana zwykła
                            p.wybuch[i][j+k].typ = wybuch;
                            p.wybuch[i][j+k].dl = czas_wybuchu;
                            
                            // jest niszczona przez wybuch
                            p.sciana[i][j+k].typ = pusty;
                            
                            break;
                        } else {
                            // sciana niezniszczalna
                            break;
                        }
                        k++;
                    }


                    // propagacja wybuchu w lewo
                    k = 0;
                    while (k <= z) {
                        if (p.sciana[i-k][j].typ == pusty) {
                            // puste pole
                            p.wybuch[i-k][j].typ = wybuch;
                            p.wybuch[i-k][j].dl = czas_wybuchu;
                        } else if (p.sciana[i-k][j].typ == zwykla) {
                            // sciana zwykła
                            p.wybuch[i-k][j].typ = wybuch;
                            p.wybuch[i-k][j].dl = czas_wybuchu;
                            
                            // jest niszczona przez wybuch
                            p.sciana[i-k][j].typ = pusty;
                            
                            break;
                        } else {
                            // sciana niezniszczalna
                            break;
                        }
                        k++;
                    }

                    // propagacja wybuchu w prawo
                    k = 0;
                    while (k <= z) {
                        if (p.sciana[i+k][j].typ == pusty) {
                            // puste pole
                            p.wybuch[i+k][j].typ = wybuch;
                            p.wybuch[i+k][j].dl = czas_wybuchu;
                        } else if (p.sciana[i+k][j].typ == zwykla) {
                            // sciana zwykła
                            p.wybuch[i+k][j].typ = wybuch;
                            p.wybuch[i+k][j].dl = czas_wybuchu;
                            
                            // jest niszczona przez wybuch
                            p.sciana[i+k][j].typ = pusty;
                            
                            break;
                        } else {
                            // sciana niezniszczalna
                            break;
                        }
                        k++;
                    }
                    
                }
            }
        }
    }
    
}

//
// Reakcja na akcje graczy
//

void co_robia_gracze()
{
    // gracz 0: strzałki
    
    int x = p.g[0].x;
    int y = p.g[0].y;
    int energia = p.g[0].energia;
    int ile_bomb = p.g[0].ile_bomb;
    bool moze_stawiac = p.g[0].moze_stawiac;
    
    if (key[ALLEGRO_KEY_LEFT] && energia > energia_ruchu) {
        if (p.sciana[x-1][y].typ == pusty && p.obiekt[x-1][y].typ != bomba) {
            energia = 0; x = x-1;
        }
    }
    if (key[ALLEGRO_KEY_RIGHT] && energia > energia_ruchu) {
        if (p.sciana[x+1][y].typ == pusty && p.obiekt[x+1][y].typ != bomba) {
            energia = 0; x = x+1;
        }
    }
    if (key[ALLEGRO_KEY_DOWN] && energia > energia_ruchu) {
        if (p.sciana[x][y+1].typ == pusty && p.obiekt[x][y+1].typ != bomba) {
            energia = 0; y = y+1;
        }
    }
    if (key[ALLEGRO_KEY_UP] && energia > energia_ruchu) {
        if (p.sciana[x][y-1].typ == pusty && p.obiekt[x][y-1].typ != bomba) {
            energia = 0; y = y-1;
        }
    }
    if (key[ALLEGRO_KEY_FULLSTOP] && p.obiekt[x][y].typ == pusty) {
        if (ile_bomb > 0 && moze_stawiac) {
            ile_bomb--;
            p.obiekt[x][y].typ = bomba;
            p.obiekt[x][y].kto = 0;
            p.obiekt[x][y].dl = dlugosc_lontu;
            moze_stawiac = false;
        }
    }
    
    p.g[0].x = x;
    p.g[0].y = y;
    p.g[0].energia = energia;
    p.g[0].ile_bomb = ile_bomb;
    p.g[0].moze_stawiac = moze_stawiac;
    
    // gracz 1: WASD
    
    x = p.g[1].x;
    y = p.g[1].y;
    energia = p.g[1].energia;
    ile_bomb = p.g[1].ile_bomb;
    moze_stawiac = p.g[1].moze_stawiac;
    
    if (key[ALLEGRO_KEY_A] && energia > energia_ruchu) {
        if (p.sciana[x-1][y].typ == pusty && p.obiekt[x-1][y].typ != bomba) {
            energia = 0; x = x-1;
        }
    }
    if (key[ALLEGRO_KEY_D] && energia > energia_ruchu) {
        if (p.sciana[x+1][y].typ == pusty && p.obiekt[x+1][y].typ != bomba) {
            energia = 0; x = x+1;
        }
    }
    if (key[ALLEGRO_KEY_S] && energia > energia_ruchu) {
        if (p.sciana[x][y+1].typ == pusty && p.obiekt[x][y+1].typ != bomba) {
            energia = 0; y = y+1;
        }
    }
    if (key[ALLEGRO_KEY_W] && energia > energia_ruchu) {
        if (p.sciana[x][y-1].typ == pusty && p.obiekt[x][y-1].typ != bomba) {
            energia = 0; y = y-1;
        }
    }
    if (key[ALLEGRO_KEY_TAB] && p.obiekt[x][y].typ == pusty) {
        if (ile_bomb > 0 && moze_stawiac) {
            ile_bomb--;
            p.obiekt[x][y].typ = bomba;
            p.obiekt[x][y].kto = 1;
            p.obiekt[x][y].dl = dlugosc_lontu;
            moze_stawiac = false;
        }
    }

    p.g[1].x = x;
    p.g[1].y = y;
    p.g[1].energia = energia;
    p.g[1].ile_bomb = ile_bomb;
    p.g[1].moze_stawiac = moze_stawiac;

}

/**************************************************************************
 * To kończy się istotna część kodu. Kod poniżej jest w miarę generyczny  *
 **************************************************************************/
 
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

int init()
{
    srandom( time(NULL) );
    
    if(!al_init()) {
        cerr << "Błąd podczas inicjalizacji allegro." << endl;
        return -1;
    }
  
    if (!al_init_primitives_addon()) {
        cerr << "Błąd podczas inicjalizacji dodatku 'primitives'." << endl;
        return -1;
    }
    
    if(!al_init_image_addon()) {
        cerr << "Błąd podczas inicjalizacji dodatku 'image'." << endl;
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

int main(int argc, char ** argv)
{
    if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }

    if (!przygotuj_bitmapy()) {
        return -1;
    }
    
    przygotuj_plansze();
    
    //
    // Event loop - główna pętla programu
    //

    bool przerysuj = true;
        
    while(!wyjdz)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            //
            // minęła 1/60 (1/FPS) część sekundy
            //
            p.g[0].energia++;
            p.g[1].energia++;
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
            
            if (ev.keyboard.keycode == ALLEGRO_KEY_FULLSTOP) {
                p.g[0].moze_stawiac = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_TAB) {
                p.g[1].moze_stawiac = true;
            }
        }

        if(przerysuj && al_is_event_queue_empty(event_queue)) {
            przerysuj = false;

            rysuj_plansze();

            al_flip_display();
         }    
    }

    if (wybuchl[0]) {
        cout << "wybuchl gracz nr 0" << endl;
    }
    if (wybuchl[1]) {
        cout << "wybuchl gracz nr 1" << endl;
    }
    
    return 0;
}
