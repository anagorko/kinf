//
// Szablon gry w Allegro 5. (C) Kółko Informatyczne Szkoły Żagle
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <iostream>
using namespace std;

const int screen_w = 1000;   // szerokość ekranu (screen width)
const int screen_h = 560;   // wysokość ekranu (screen height)

const int wiel = 20;

const int sz = (screen_w - 100) / wiel;
const int wy = screen_h / wiel;

/*********************************
 * Tu piszecie swoje rozwiązania *
 *********************************/

// rozmiary planszy: sz x wy
int grid[sz][wy];
int zero = 0;
void wyczysc()
{
    for (int x = 0; x < sz; x++) {
        for (int y = 0; y < wy; y++) {
            grid[x][y] = 0;
        }
    }
}

void odwroc()
{
	for (int x = 0; x < sz; x++) {
		for (int y = 0; y < wy; y++) {
			if (grid[x][y] == 0){
				grid[x][y] = 1;
		       	}
			else{
				grid[x][y] = 0;
			}
		}
	}
}

void szachownica()
{
	for (int x = 0; x < sz; x++) {
		for (int y = 0; y < wy; y++) {
			if (x % 2 == 0){
				grid[x][y] = 1;
			}else {
				grid[x][y] = 0;
			}
		}
	}


}

void paski()
{
	for (int x = 0; x < sz; x++) {
		for (int y = 0; y < wy; y++) {
			if (x % 2 == 0){
				grid[x][y] = 1;
			}else {
				grid[x][y] = 0;
			}
		}
	}
    
}

void flaga()
{
}

void prostokaty()
{
}

void kolo()
{
}

void kwiat()
{
}

/********************************************************
 * Dalej nie musicie nic zmieniać (choć nikt nie broni) *
 ********************************************************/

//
// Zmienne
//

ALLEGRO_FONT *font;
    
bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze
int mouse_x;
int mouse_y;
bool mouse_pressed = false;



//
// Rysowanie przycisku
//

typedef struct przycisk
{
    int x1, y1, x2, y2;
    string napis;
};

przycisk przyciski[123];
int ile_przyciskow = 0;

void dodaj_przycisk(przycisk p)
{
    przyciski[ile_przyciskow++] = p;    
}

void rysuj_przycisk(przycisk &p)
{    
    ALLEGRO_COLOR bg;
    
    if (p.x1 <= mouse_x && mouse_x <= p.x2 &&
        p.y1 < mouse_y && mouse_y <= p.y2) {
        if (mouse_pressed) {
            bg = al_map_rgb(200,0,0);
        } else {
            bg = al_map_rgb(50,50,50);
        }
    } else {
        bg = al_map_rgb(0,0,200);
    }
    
    al_draw_filled_rectangle(p.x1, p.y1, p.x2, p.y2, bg);    
    al_draw_text(font, al_map_rgb(255,255,255), (p.x1+p.x2)/2, (p.y1+p.y2)/2-6,ALLEGRO_ALIGN_CENTRE, p.napis.c_str());
}

void rysuj_przyciski()
{
    for (int i = 0; i < ile_przyciskow; i++) {
        rysuj_przycisk(przyciski[i]);
    }
}

//
// Rysowanie planszy
//

void rysuj_plansze()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    
    for (int x = 0; x < sz; x++) {
        for (int y = 0; y < wy; y++) {
            if (grid[x][y] == 0) {
                al_draw_filled_rectangle(x * wiel, y * wiel, (x+1) * wiel - 1, (y+1)* wiel - 1, al_map_rgb(128,128,255));
            } else {
                al_draw_filled_rectangle(x * wiel, y * wiel, (x+1) * wiel - 1, (y+1)* wiel - 1, al_map_rgb(255,128,128));
            }
        }
    }
}

//
// Mechanika gry
//

void aktualizuj_plansze()
{
    if (mouse_pressed) {
        if (mouse_x < screen_w - 100) {
            int click_x = mouse_x / wiel;
            int click_y = mouse_y / wiel;
            
            if (click_x >= 0 && click_x < sz && click_y >= 0 && click_y < wy) {
                grid[click_x][click_y] = 1 - grid[click_x][click_y];
            }
            
            mouse_pressed = false;
        } else {
            for (int i = 0; i < ile_przyciskow; i++) {
                przycisk p = przyciski[i];
                if (p.x1 <= mouse_x && mouse_x <= p.x2 &&
                    p.y1 < mouse_y && mouse_y <= p.y2) {
                    
                    switch(i) {
                    case 0: wyczysc(); break;
                    case 1: odwroc(); break;
                    case 2: szachownica(); break;
                    case 3: paski(); break;
                    case 4: flaga(); break;
                    case 5: prostokaty(); break;
                    case 6: kolo(); break;
                    case 7: kwiat(); break;
                    default:
                        ;
                    }                        
                }
            }
            mouse_pressed = false;
        }
    }
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
    
    if(!al_install_keyboard()) {
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

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    font = al_load_ttf_font("FreeMono.ttf",12,0);
  
    if (!font) {
        cerr << "Nie mogę załadować czcionki FreeMono.ttf" << endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
  
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

    dodaj_przycisk( (przycisk) { screen_w - 90, 8, screen_w - 10, 40, "Wyczyść" });
    dodaj_przycisk( (przycisk) { screen_w - 90, 48, screen_w - 10, 80, "Odwróć" });
    dodaj_przycisk( (przycisk) { screen_w - 90, 88, screen_w - 10, 120, "Szachownica" });
    dodaj_przycisk( (przycisk) { screen_w - 90, 128, screen_w - 10, 160, "Paski" });
    dodaj_przycisk( (przycisk) { screen_w - 90, 168, screen_w - 10, 200, "Flaga" });
    dodaj_przycisk( (przycisk) { screen_w - 90, 208, screen_w - 10, 240, "Prostokąty" });
    dodaj_przycisk( (przycisk) { screen_w - 90, 248, screen_w - 10, 280, "Koło" });
    dodaj_przycisk( (przycisk) { screen_w - 90, 288, screen_w - 10, 320, "Kwiat" });
    
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
            break;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
            ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) { 
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
            rysuj_przyciski();
            
            al_flip_display();
         }    
    }

    return 0;
}
