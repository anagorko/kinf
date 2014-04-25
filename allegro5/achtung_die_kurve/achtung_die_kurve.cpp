//
// Achtung die kurve
// zrobiony przy pomocy szablonu gry w Allegro 5.
// (C) Kółko Informatyczne Szkoły Żagle 
//
/*                                                           _____________
                                                             \  __________\ 
       ______   ___    ___                                   \\ \_________I
      /\  _  \ /\_ \  /\_ \                                   \\ \_________
      \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___       \\_________ \
       \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\      \/_______/\ \
        \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \       _______\_\ \
         \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/      /\___________\
          \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/       \/___________/ 
                                         /\____/
                                         \_/__/
     New mouse API.
     By Peter Wang. EDITED by Jan Łukomski
     See readme.txt for copyright information.
*/

#include <iomanip>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sstream>

#include <stdio.h>
#include <string.h>


#include <iostream>
using namespace std;


const int screen_w = 1366;   // szerokość ekranu (screen width)
const int screen_h = 768;   // wysokość ekranu (screen height)

/****************************************
 * Kod poniżej jest w miarę generyczny  *
 ****************************************/
 
const float FPS = 1000; //60      // Frames Per Second
bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP * snakes = NULL;
ALLEGRO_BITMAP * pause_menu = NULL;
ALLEGRO_BITMAP * menu0_bitmap = NULL;
ALLEGRO_FONT * font = NULL;
ALLEGRO_FONT * font1 = NULL;


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

	font=al_load_ttf_font("FreeMono.ttf", 60, 12);
	font1=al_load_ttf_font("FreeMono.ttf", 30, 12);

   if (!font) {
       cerr << "Nie mogę załadować czcionki FreeMono.ttf" << endl;
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
 	al_stop_timer(timer);

    return 0;
}
/****************************************
 * Tu rozpoczyna się istotna część kodu *
 ****************************************/

//
//kofiguracja gry
//
	const int number_of_player=2;
	const int xpl=1082;//1071
	const int ypl=690;//688
	//licznik

	int czas=0;
	stringstream ss_time;

	bool by_the_network=false;
	
//
// Struktury danych
//
	struct type_of_player{
		float x;
		float y;
		float step;
		float radius_table;
		float radius;
		float space;
		float alfa;
		float degrees;
		int lastczas;
		int color0;
		int color1;
		int color2;
		bool touch;
		float spacetime;
	};
	type_of_player player[number_of_player];
	struct type{
		int nrplayer;
		int time;
	};
	type board[xpl][ypl];//+2

//
// Zmienne
//
	bool przegrales=false;
    bool dotyka=false;
    bool wyjdz = false;
    int cursor_x;
    int cursor_y;
    
//
//Czyszczenie
//
void menu0(){
	
	while(true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            key[ev.keyboard.keycode] = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            key[ev.keyboard.keycode] = false ;

            if (ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                wyjdz=true;
                break;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            	wyjdz=true;
            	 break;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_1){
            	break;

            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_2){
            	by_the_network=true;
            	break;
            }
        }

        if(al_is_event_queue_empty(event_queue)) {
            
            al_flip_display();
         }
	}
	al_start_timer(timer);
}
void menu_quit()
{
	ALLEGRO_EVENT ev;
	al_draw_bitmap(pause_menu, 0, 0, 0);
	al_flip_display();
	al_stop_timer(timer);
	while(true){
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            key[ev.keyboard.keycode] = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            key[ev.keyboard.keycode] = false ;

            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                break;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                wyjdz = true;
                break;
            }
        }
	}
	al_start_timer(timer);
}
	void clean()
{
	system ("../../network/websockets/./server&");
	system ("i=`ps a | pgrep server`; kill $i");
	srandom(time(NULL)+getpid());
	for(int i=1;i<xpl;i++){
		for(int a=1;a<ypl;a++){
		board[i][a].nrplayer=-1;
		board[i][a].time=-1;
		}
	}
	for(int i=0;i<xpl;i++){
	board[i][0].nrplayer=100;
	board[i][ypl-1].nrplayer=100;
	board[i][0].time=-100;
	board[i][ypl-1].time=-100;
		if(i<ypl){
		board[0][i].nrplayer=100;
		board[xpl-1][i].nrplayer=100;
		board[0][i].time=-100;
		board[xpl-1][i].time=-100;
		}
	}
	for(int i=0;i<number_of_player;i++){
		player[i].x=5;//pozycja x;
		player[i].y=5;//pozycja y;
		player[i].radius=5;//promien weza
		player[i].step=0.10;//dlugosc kroku weza
		player[i].space=420;//czas ponizej ktorego jest naliczana kolizja
		player[i].spacetime=100;//co jaki czas oczytuje czy klawisz jedt wcisnienty
		player[i].alfa=0.5;//wrazliwosc skrecania
		player[i].degrees=0;//kierunek poczatkowy gracza
		player[i].touch=false;
		player[i].lastczas=0;//czas ostatniego wcisniencia klawisza
		while(player[i].x<=20+player[i].radius || player[i].y<=20+player[i].radius){
			player[i].x=random()%1072-2*player[i].radius;
			player[i].y=random()%679-2*player[i].radius;
		}
		switch(i){
		case 0:
			player[i].color0=0;
			player[i].color1=23;
			player[i].color2=155;
			break;
		case 1:
			player[i].color0=37;
			player[i].color1=164;
			player[i].color2=40;
			break;
		}
	}
	snakes = al_create_bitmap(1080,687);
	pause_menu = al_create_bitmap(screen_w,screen_h);
	menu0_bitmap = al_create_bitmap(screen_w,screen_h);
	al_set_target_bitmap(snakes);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	for(int i=0;i<number_of_player;i++){
 	al_draw_filled_circle(player[i].x, player[i].y-1, player[i].radius, al_map_rgb(player[i].color0, player[i].color1, player[i].color2));
	}
	al_set_target_backbuffer(display);
	al_set_target_bitmap(pause_menu);
	al_clear_to_color(al_map_rgba(0, 0, 0, 200));
	al_set_target_backbuffer(display);
	al_set_target_bitmap(menu0_bitmap);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_target_backbuffer(display);
}

//
// Rysowanie planszy
//

void rysuj_plansze()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_rectangle(19, 19, 1101, 709, al_map_rgb(255, 255, 255), 0 );//x1,y1,x2,y2,kolor,szerokosc;
	al_set_target_bitmap(snakes);
//	WYSWIETLANIE WEZY
	for(int i=0;i<number_of_player;i++){
 		al_draw_filled_circle(player[i].x, player[i].y-1, player[i].radius, al_map_rgb(player[i].color0, player[i].color1, player[i].color2));
	}
	al_set_target_backbuffer(display);
	al_draw_bitmap(snakes, 20, 20, 0);
//	#################
//	WYSWIETLANIE TIMERA
	float stoper=clock()/100000.0;
	ss_time << fixed << setprecision(1) << stoper;
	string tekst =  ss_time.str();
	int przesuniencie_timera=0;
	if(tekst.length()==4){przesuniencie_timera=15;}
	if(tekst.length()==5){przesuniencie_timera=35;}
	if(tekst.length()==6){przesuniencie_timera=50;}
	al_draw_text(font, al_map_rgb(255,255,255), 1180-przesuniencie_timera, 0,0, tekst.c_str());
	ss_time.clear();
	tekst="sekund";
	al_draw_text(font1, al_map_rgb(255,255,255), 1180, 70,0, tekst.c_str());
	ss_time.str("");
//	###################


}

//
// Mechanika gry
//

void aktualizuj_plansze()
{
	czas++;
	for(int i=0;i<number_of_player;i++){
		if(player[i].touch){continue;}
		player[i].x=player[i].x+player[i].step*cos(player[i].degrees);
		player[i].y=player[i].y+player[i].step*sin(player[i].degrees);
		for(int a=0;a<2*player[i].radius;a++){
			for(int e=0;e<2*player[i].radius;e++){
				float f_iks=player[i].x-player[i].radius+a;
				float f_igrek=player[i].y-player[i].radius+e;
				if (f_iks < 0) { f_iks = 0; }
				if (f_igrek < 0) { f_igrek = 0; }
				if (f_iks > xpl-1) { f_iks = xpl-1; }
				if (f_igrek > ypl-1) { f_igrek = ypl-1; }

				if((f_igrek-player[i].y)*(f_igrek-player[i].y)+(player[i].x-f_iks)*(player[i].x-f_iks)<player[i].radius*player[i].radius){
					int iks = (int) f_iks;
					int igrek = (int) f_igrek;

					if(board[iks][igrek].nrplayer!=-1){
						if(board[iks][igrek].nrplayer==i){
							if(board[iks][igrek].time<czas-player[i].space){
								cout<<"GRACZ "<<i<<": wjechales w siebie"<<endl;
//								przegrales=true;
         					      	        player[i].touch = true;
								break;
							}
						}else if(board[iks][igrek].nrplayer!=100){
							cout<<"GRACZ "<<i<<": wiechales w kolege"<<endl;
//							przegrales=true;
        	        			        player[i].touch = true;
							break;
						}else if(board[iks][igrek].nrplayer==100){
							cout<<"GRACZ "<<i<<": wjechales w sciane"<<endl;
//							przegrales=true;
        	               				player[i].touch = true;
							break;
						}
					}else{
						board[iks][igrek].nrplayer=i;
						board[iks][igrek].time=czas;
					}
				}
			if(player[i].touch){break;}
			}
		}
	}
}

//
// Reakcja na akcje graczy
//

void co_robia_gracze()
{
	if(key[ALLEGRO_KEY_LEFT] && czas-player[0].lastczas>player[0].spacetime){
	player[0].degrees=player[0].degrees-player[0].alfa;
	player[0].lastczas=czas;
	}
	if(key[ALLEGRO_KEY_RIGHT] && czas-player[0].lastczas>player[0].spacetime){
	player[0].degrees=player[0].degrees+player[0].alfa;
	player[0].lastczas=czas;
	}
	if(number_of_player>=2){
		if(key[ALLEGRO_KEY_Z] && czas-player[1].lastczas>player[1].spacetime){
		player[1].degrees=player[1].degrees-player[1].alfa;
		player[1].lastczas=czas;
		}
		if(key[ALLEGRO_KEY_X] && czas-player[1].lastczas>player[1].spacetime){
                player[1].degrees=player[1].degrees+player[1].alfa;
                player[1].lastczas=czas;
		}
	
	}

}



int main(int argc, char ** argv)
{
   
 	if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }

    bool przerysuj = true;
    
	clean();

	menu0();
    
   	//
    // Event loop - główna pętla programu
    //
        
    while(!wyjdz && !przegrales)
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
            key[ev.keyboard.keycode] = false ;

            if (ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                wyjdz = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            	menu_quit();
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
