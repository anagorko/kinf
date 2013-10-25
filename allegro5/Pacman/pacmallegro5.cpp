//
// Szablon gry w Allegro 5. (C) Kółko Informatyczne Szkoły Żagle
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include "allegro5/allegro_native_dialog.h"
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
	

	int x = screen_w/2+100, y = screen_h/2 + 100;// zmienne pacmana
	int xst = screen_w/2, yst = screen_h/2;
	int odl, wysoko;

	
//
// Rysowanie planszy
//

void rysuj_plansze()
{
    al_clear_to_color(al_map_rgb(0,0,0));
}

//
// Mechanika gry
//

void aktualizuj_plansze()
{
		odl = screen_w - x;		
		wysoko = screen_h - y;

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
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP  *stwor_prawoup   = NULL;
	ALLEGRO_BITMAP  *stwor_lewoup   = NULL;
	ALLEGRO_BITMAP  *stwor_prawodol   = NULL;
	ALLEGRO_BITMAP  *stwor_lewodol   = NULL;
	ALLEGRO_BITMAP  *pacman_lewo   = NULL;
	ALLEGRO_BITMAP  *pacman_prawo   = NULL;
	ALLEGRO_BITMAP  *pacman_dol   = NULL;
	ALLEGRO_BITMAP  *pacman_up   = NULL;
	ALLEGRO_BITMAP  *pacman  = NULL;
	ALLEGRO_BITMAP  *stwor   = NULL;

	stwor_prawoup = al_load_bitmap("stwor.tga");
	stwor_lewoup = al_load_bitmap("stwor4.tga");
	stwor_prawodol = al_load_bitmap("stwor1.tga");
	stwor_lewodol = al_load_bitmap("stwor2.tga");			
	pacman_lewo = al_load_bitmap("pacman.tga");	
	pacman_prawo = al_load_bitmap("pacman1.tga");	
	pacman_dol = al_load_bitmap("pacman2.tga");	
	pacman_up = al_load_bitmap("pacman3.tga");
	pacman = pacman_prawo;
	stwor = stwor_prawoup;
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
