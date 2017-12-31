//
// Szablon gry w Allegro 5. (C) Kółko Informatyczne Szkoły Żagle
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


#include <stdio.h>
#include <string.h>

#include<ctime>

#include <iostream>
using namespace std;

//
// Konfiguracja gry
//

const int size_x = 125;
const int size_y = 350;

const int screen_w = 1280;   // szerokość ekranu (screen width)
const int screen_h = 800;   // wysokość ekranu (screen height)

ALLEGRO_FONT * font = NULL;

/****************************************
 * Tu rozpoczyna się istotna część kodu *
 ****************************************/
 
//
// Zmienne czasu
//

string int_to_string(int n)
{
    string s = "";
    if ( n < 10 )
    {
        s =  "0";
        s = s + ((char) (n + ((int) '0') ));
    }
    else
    {
        s = ((char) (n / 10 + ((int) '0') ) );
        s = s + ((char) (n % 10 + ((int) '0') ) );
    }

    return s;
}


string odliczenie()
{
    struct tm nowyrok;

    int s,m,g;

    nowyrok.tm_hour = 0;
    nowyrok.tm_min = 0;
    nowyrok.tm_sec = 0;
    nowyrok.tm_year = 118; //1900 + tm_year = numer nadzchodzącego roku
    nowyrok.tm_mon = 0;
    nowyrok.tm_mday = 1;

    time_t teraz, nowy_rok;

    time(&teraz);

    nowy_rok = mktime(&nowyrok);

    s = difftime(nowy_rok, teraz);
    g = s/3600 + 1;
    m = ( s / 60 ) % 60;
    s = s % 60;

    string time;

    cout << g << ":" << m << ":" << s << endl;

    if( g == 0 )
    {
        time = int_to_string(m) + ":" + int_to_string(s);
    }
    else
    {
        time = int_to_string(g) + ":" + int_to_string(m);
    }

    return time;
}

//
// Rysowanie planszy
//

void rysuj_plansze()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    string tekst = odliczenie();
    double px = screen_w/2 - (( tekst.length() * size_x )) + 100 ;
    double py = screen_h/2 - ( size_y );
    al_draw_text(font, al_map_rgb(255,255,255), px, py,0, tekst.c_str());
}

//
// Mechanika gry
//

void aktualizuj_plansze()
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
    al_init_font_addon();
    al_init_ttf_addon();

    font = al_load_ttf_font("FreeMono.ttf", size_y, size_x);
  
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
        
    while(!wyjdz)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            //
            // minęła 1/60 (1/FPS) część sekundy
            //
            przerysuj = true; 

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
