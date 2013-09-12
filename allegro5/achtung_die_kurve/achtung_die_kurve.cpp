//
// Achtung die kurve
// zrobiony przy pomocy szablonu gry w Allegro 5.
// (C) Kółko Informatyczne Szkoły Żagle
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
using namespace std;


const int screen_w = 1366;   // szerokość ekranu (screen width)
const int screen_h = 768;   // wysokość ekranu (screen height)

/****************************************
 * Kod poniżej jest w miarę generyczny  *
 ****************************************/
 
const float FPS = 60;       // Frames Per Second
bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP * snakes = NULL;


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
/****************************************
 * Tu rozpoczyna się istotna część kodu *
 ****************************************/

//
//kofiguracja gry
//
	int xpl=1071;
	int ypl=688;
	int czas=0;
	//player1
	float xplayer1=5;
	float yplayer1=5;
	float stepplayer1=10;
	float radiusplayer1=10;//promień 
	float spaceplayer1=5;

//
// Struktury danych
//
	typedef struct type{
		int player;
		int time;
	};
	type board[1071][688];//+2

//
// Zmienne
//

//
//Czyszczenie
//
void clean()
{
	srandom(time(NULL)+getpid());
	for(int i=1;i<1070;i++){
		for(int a=1;a<687;a++){
		board[i][a].player=-1;
		board[i][a].time=-1;
		}
	}
	for(int i=0;i<1071;i++){
	board[i][0].player=100;
	board[i][687].player=100;
	board[i][0].time=-100;
	board[i][687].time=-100;
		if(i<688){
		board[0][i].player=100;
		board[1070][i].player=100;
		board[0][i].time=-100;
		board[1070][i].time=-100;
		}
	}
	while(xplayer1<=20+radiusplayer1 || yplayer1<=20+radiusplayer1){
	xplayer1=random()%1070-2*radiusplayer1;
	yplayer1=random()%687-2*radiusplayer1;
	}
	for(int i=0;i<radiusplayer1;i++){
		for(int a=0;a<radiusplayer1;a++){
			int iks=xplayer1-(radiusplayer1/2)+i;
			int igrek=yplayer1-(radiusplayer1/2)+a;
			if((igrek-yplayer1)*(igrek-yplayer1)+(xplayer1-iks)*(xplayer1-iks)<radiusplayer1*radiusplayer1){
				board[iks][igrek].time=czas;
				board[iks][igrek].player=1;
			}
		}
	}
	snakes = al_create_bitmap(1090,697);
	al_set_target_bitmap(snakes);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_draw_filled_circle(xplayer1,yplayer1, radiusplayer1, al_map_rgb(155,23,0));
	al_set_target_backbuffer(display);
}

//
// Rysowanie planszy
//

void rysuj_plansze()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_rectangle(10, 10, 1100, 707, al_map_rgb(255, 255, 255), 10 );//x1,y1,x2,y2,kolor,szerokosc;
	al_draw_bitmap(snakes, 10, 10, 0);
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
	if(key[ALLEGRO_KEY_LEFT]){
	}


}



int main(int argc, char ** argv)
{
    if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }

    bool przerysuj = true;
    bool wyjdz = false;  

	clean();
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
