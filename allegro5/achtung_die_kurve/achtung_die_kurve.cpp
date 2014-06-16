//
// Achtung die kurve
// zrobiony przy pomocy szablonu gry w Allegro 5.
// (C) Kółko Informatyczne Szkoły Żagle 
//
/*                                                           ____________
                                                             \  _________\ 
       ______   ___    ___                                   \\ \________I
      /\  _  \ /\_ \  /\_ \                                   \\ \_________
      \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___       \\_________ \
       \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\      V________/\ \
        \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \        ______\_\ \
         \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/       /\__________\
          \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/        \/__________/ 
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
#include <string>

#include <stdio.h>
#include <string.h>

//#include "run.cpp"

#include <iostream>
using namespace std;


const int screen_w = 1366;   // szerokość ekranu (screen width)
const int screen_h = 768;   //wysokość ekranu (screen height)

/****************************************
 * Kod poniżej jest w miarę generyczny  *
 ****************************************/
 
const float FPS = 60; //60      // Frames Per Second
bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER * timer = NULL;
ALLEGRO_BITMAP * snakes = NULL;
ALLEGRO_BITMAP * pause_menu = NULL;
ALLEGRO_BITMAP * menu0_bitmap = NULL;
ALLEGRO_BITMAP * gameroom_bitmap = NULL;
ALLEGRO_BITMAP * podsumowanie_wynikow_bitmap = NULL;
ALLEGRO_BITMAP * zaciemnienie_bitmap = NULL;
ALLEGRO_FONT * font = NULL;
ALLEGRO_FONT * font1 = NULL;
ALLEGRO_FONT * font2 = NULL;
ALLEGRO_FONT * font3 = NULL;
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

    
    
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

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
	font2=al_load_ttf_font("FreeMono.ttf", 20, 12);
	font3=al_load_ttf_font("FreeMono.ttf", 60, 12);

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
/****************************************
 * Tu rozpoczyna się istotna część kodu *
 ****************************************/

//
//kofiguracja gry
//
 	int number_of_player=2;
	const int max_number_of_player=10;
	const int xpl=1082;//1071
	const int ypl=690;//688
	//licznik

	int czas=0;
	stringstream ss_time;
	int przesuniecie_czasu=0;
	int czasomierz=0;
	int licznik_fps;

//
// Zmienne
//
	int przegranych=0;
    bool wyjdz = false;
    int cursor_x;
    int cursor_y;
    bool cursor_pressed=false;

    int wybrane_kolory=0;
    bool klik_down=false;
    bool koncz_gre=false;
    bool zacznij_gre;


    int pocz_zakresu_x_0 = 200;
	int kon_zakresu_x_0 = 600;
	int pocz_zakresu_x_1 = 700;
	int kon_zakresu_x_1 = 1100;
	int pocz_zakresu_y = 200;
	int kon_zakresu_y = 700;


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
		int color;
		int touch;
		float touch_time;
		float spacetime;
		int przerwa;//licznik przerwy
		int przerwa_time;//czas kiedy ma byc wykonywana przerwa
	};
	type_of_player player[max_number_of_player];
	
	struct type{
		int nrplayer;
		int time;
	};
	type board[xpl][ypl];//+2

	class type_color{
	public:
	 	int _r;
	 	int _g;
	 	int _b;
	 	int x;
	 	int y;
	 	int bok;
	 	int animation;
	 	int size_animation;
	 	bool wykozystany;
	 	bool touch;
	 	void draw(){
	 		al_set_target_bitmap(gameroom_bitmap);
	 		al_draw_filled_rectangle(x-animation, y-animation, x+bok+animation, y+bok+animation,al_map_rgb(_r , _g, _b));
	 		if(wykozystany){
	 			string tekst="wykorzystany kolor";
				al_draw_text(font2, al_map_rgb(255,255,255),x+15,y+bok/2-15, 0, tekst.c_str());
			}
	 		al_set_target_backbuffer(display);
	 	}
	 	void calculate(int i){
	 		if(cursor_x>x && cursor_x<x+bok && cursor_y>y && cursor_y<y+bok){
	 			touch=true;
	 			if(klik_down && !cursor_pressed){
	 				if(!wykozystany){
	 					if(player[0].color==-1){
							wybrane_kolory++;	
							player[0].color=i;	
							cout<<"player[0].color="<<player[0].color<<endl;
							wykozystany=true;
						}else if(player[1].color==-1){
							wybrane_kolory++;	
							player[1].color=i;
							cout<<"player[1].color="<<player[1].color<<endl;
							wykozystany=true;
						}
					}else{
	 					if(player[0].color==i){
							wybrane_kolory--;	
							player[0].color=-1;
							wykozystany=false;	
						}else if(player[1].color==i){
							wybrane_kolory--;	
							player[1].color=-1;
							wykozystany=false;
						}
	 				}
	 				klik_down=false;
	 			}
	 		}else{
	 			touch=false;
	 		}
	 		if(animation<size_animation && touch){animation++;}
			if(animation>0 && !touch){animation--;}


	 		

	 	}
	};
	type_color colors[10];

	class button{
	public:
		int px;
		int py;
		int kx;
		int ky;
		int r;
		int g;
		int b;
		bool touch;
		int animation;
		int size_animation;
		string tekst;
		void init(){

		}
		void calculate(){
			if(cursor_x>px && cursor_x<kx && cursor_y>py && cursor_y<ky){
		if(animation<size_animation && touch){animation++;}
			if(animation>0 && !touch){animation--;}		touch=true;
				if(klik_down && !cursor_pressed){
					if(wybrane_kolory==2){
						zacznij_gre=true;
					}
					klik_down=false;
				}
			}else{
				touch=false;
			}
			if(animation<size_animation && touch){animation++;}
			if(animation>0 && !touch){animation--;}
		}
		void draw(){
			al_set_target_bitmap(gameroom_bitmap);
			al_draw_filled_rounded_rectangle(px-animation, py-animation, kx+animation, ky+animation, 5, 20, al_map_rgb(r,g,b));
			if(tekst=="START"){
				al_draw_text(font1, al_map_rgb(255,255,255), px+5, py,0, tekst.c_str());
			}
			al_set_target_backbuffer(display);
		}
	};
	button start;
    
//
//Czyszczenie
//

void rysowanie_kolorow();
void gameroom()
{

	cout<<"GAMEROOM\n";
    	
	bool przerysuj = true;
	zacznij_gre=false;
	int klikanie=0;

	 while(!zacznij_gre)
	 {
	    ALLEGRO_EVENT ev;
   	    al_wait_for_event(event_queue, &ev);

       	if(ev.type == ALLEGRO_EVENT_TIMER) {
            //
            // minęła 1/60 (1/FPS) część sekundy
            //
           
           przerysuj = true;
          
           start.calculate();
           start.draw();
           for(int i=0;i<10;i++){
           	colors[i].calculate(i);
           	colors[i].draw();
           }

           if(klik_down){
           	klikanie++;
           }else{
           	klikanie=0;
           }
           if(klikanie==10){klik_down=false;}
           	
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        	key[ev.keyboard.keycode] = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            key[ev.keyboard.keycode] = false ;

       	    if (ev.keyboard.keycode == ALLEGRO_KEY_Q) {
      	        wyjdz = true;
      	        koncz_gre = true;
      	        break;
       	    }
       	    if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
       	    	wyjdz = true;
       	    	koncz_gre = true;
       	    	break;
       	    }
       	    if (ev.keyboard.keycode == ALLEGRO_KEY_S && wybrane_kolory==2){
       	    	break;
       	    }
   		} else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
           	cursor_x = ev.mouse.x;
           	cursor_y = ev.mouse.y;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            cursor_pressed = false;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            cursor_pressed = true;
            klik_down=true;
        }

      	if(przerysuj && al_is_event_queue_empty(event_queue)) {
       	    przerysuj = false;

			
		

       	    al_draw_bitmap(gameroom_bitmap, 0, 0, 0);
       	   	al_flip_display();

           	al_set_target_bitmap(gameroom_bitmap);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			string tekst="Wybierz kolory graczy";
			al_draw_text(font1, al_map_rgb(255,255,255), 480, 120,0, tekst.c_str());
			tekst="ABY ZAKOŃCZYĆ, NACIŚNIJ Q";
			al_draw_text(font2, al_map_rgb(255,255,255), 1050, 20,0, tekst.c_str());
			tekst="Achtung die kurve";
			al_draw_text(font3, al_map_rgb(255,22,22), 350, 10, 0, tekst.c_str());
			al_set_target_backbuffer(display);
    	}
	}
}

void konczenie_tury(){
	stringstream ss;
	for(int i=0;i<number_of_player;i++){
		if(player[i].touch!=-1){continue;}
		if(player[i].przerwa==0 && player[i].przerwa_time==0){
			player[i].przerwa_time=(czasomierz+100)+(random()%900);
		}
	}
}

void podsumowanie_wynikow(){
	
	stringstream ss;
	

	int przesuniecie_tekstu=215;
	
	int bok=70;
	int px=480,py=220;
	int odstep=40;

	int licznik=1;
	al_set_target_bitmap(podsumowanie_wynikow_bitmap);
	for(int i=number_of_player-1;i>=0;i--){
		for(int a=0;a<number_of_player;a++){
			if(player[a].touch==i){
				ss.str("");ss.clear();
				ss<<licznik<<".";
				string tekst =  ss.str();
				al_draw_text(font, al_map_rgb(255,255,255), 400, przesuniecie_tekstu, 0, tekst.c_str());
				ss.str("");ss.clear();
				ss << fixed << setprecision(1) << player[a].touch_time;
				tekst = ss.str();
				al_draw_text(font, al_map_rgb(255,255,255), 600, przesuniecie_tekstu, 0, tekst.c_str());
				//al_draw_filled_rectangle(480, przesuniecie+30,530,przesuniecie+60,al_map_rgb(colors[player[a].color]._r,colors[player[a].color]._g,colors[player[a].color]._b));
				al_draw_filled_rectangle(px, py,px+bok,py+bok,al_map_rgb(colors[player[a].color]._r,colors[player[a].color]._g,colors[player[a].color]._b));
				przesuniecie_tekstu=przesuniecie_tekstu+110;
				licznik++;
				py=py+bok+odstep;
			}
		}
	}
	al_set_target_backbuffer(display);

	al_draw_bitmap(podsumowanie_wynikow_bitmap, 0, 0, 0);

	al_flip_display();

	while(!wyjdz)
   	{
   		ALLEGRO_EVENT ev;
   	  	al_wait_for_event(event_queue, &ev);

    	if(ev.type == ALLEGRO_EVENT_TIMER) {
	   	   //
      	   // minęła 1/60 (1/FPS) część sekundy
       	   //

       	   if(cursor_pressed){
       	   	cursor_pressed=false;
       	   	break;
       	   }


       	} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
           key[ev.keyboard.keycode] = true;
       	} else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
       	    key[ev.keyboard.keycode] = false ;
        
            if (ev.keyboard.keycode == ALLEGRO_KEY_Q) {
       	        wyjdz = true;
       	        koncz_gre = true;
       	    }
       	    if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
       	    	break;
       	    }
       	} else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            cursor_x = ev.mouse.x;
            cursor_y = ev.mouse.y;
   		} else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            cursor_pressed = false;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            cursor_pressed = true;
        }
	}
}
void clean0(){
	snakes = al_create_bitmap(1080,687);
	pause_menu = al_create_bitmap(screen_w,screen_h);
	menu0_bitmap = al_create_bitmap(screen_w,screen_h);
	gameroom_bitmap = al_create_bitmap(screen_w,screen_h);
	podsumowanie_wynikow_bitmap = al_create_bitmap(1366, 768);
	zaciemnienie_bitmap = al_create_bitmap(1366, 768);

	//czyszczenie class start
		start.px=1150;
		start.py=100;
		start.kx=1250;
		start.ky=150;
		start.r=15;
		start.g=15;
		start.b=15;
		start.touch=false;
		start.animation=0;
		start.size_animation=10;
		start.tekst="START";
	
}
void clean2(){
	cout<<"jesetem w cleanie2"<<endl;
	for(int i=0;i<number_of_player;i++){
		player[i].x=5;//pozycja x;
		player[i].y=5;//pozycja y;
		player[i].radius=3;//promien weza
		player[i].step=2.0;//dlugosc kroku weza
		player[i].space=10;//czas ponizej ktorego jest naliczana kolizja
		player[i].spacetime=0;//co jaki czas oczytuje czy klawisz jedt wcisnienty
		player[i].alfa=0.1;//wrazliwosc skrecania
		player[i].degrees=0;//kierunek poczatkowy gracza
		player[i].touch=-1;
		player[i].lastczas=0;//czas ostatniego wcisniencia klawisza
		player[i].przerwa=0;//licznik przerwy
		player[i].przerwa_time=0;//czas kiedy ma byc przerwa gracza
		while(player[i].x<=20+player[i].radius || player[i].y<=20+player[i].radius){
			player[i].x=random()%1072-2*player[i].radius;
			player[i].y=random()%679-2*player[i].radius;
		}
	}
	przesuniecie_czasu=clock()-10000;
	czasomierz=0;
}


void menu_quit()
{
	int licznik_czasu=0;
	ALLEGRO_EVENT ev;
	al_stop_timer(timer);
	al_draw_bitmap(zaciemnienie_bitmap, 0, 0, 0);
	int px=480;
	int py=300;
	al_set_target_bitmap(pause_menu);
	string tekst="Achtung die kurve";
	al_draw_text(font3, al_map_rgb(255,22,22), 250, 100, 0, tekst.c_str());
	tekst="STOP";
	al_draw_text(font3, al_map_rgb(255,100,255), px, py, 0, tekst.c_str());
	al_set_target_backbuffer(display);

	al_draw_bitmap(pause_menu, 0, 0, 0);
	al_flip_display();
	
	while(true){
		al_wait_for_event(event_queue, &ev);
		if(licznik_czasu==0) {

		

		}else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            key[ev.keyboard.keycode] = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            key[ev.keyboard.keycode] = false ;

            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE || ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                break;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                wyjdz = true;
                koncz_gre = true;
                break;
            }
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            cursor_x = ev.mouse.x;
            cursor_y = ev.mouse.y;
   		} else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            cursor_pressed = false;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            cursor_pressed = true;
        } 

       	if(licznik_czasu==0 && al_is_event_queue_empty(event_queue)) {
 			al_draw_bitmap(pause_menu, 0, 0, 0);
           	al_flip_display();
       	}
       	licznik_czasu=(licznik_czasu+1)%20;
	}
	al_start_timer(timer);
}
void clean1()
{
	
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
	string tekst;
	al_set_target_bitmap(snakes);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_set_target_backbuffer(display);
	al_set_target_backbuffer(display);
	al_set_target_bitmap(pause_menu);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_set_target_backbuffer(display);
	al_set_target_bitmap(menu0_bitmap);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	tekst="Achtung die kurve";
	al_draw_text(font, al_map_rgb(255,100,255), 350, 50, 0, tekst.c_str());
	al_set_target_backbuffer(display);
	al_set_target_bitmap(gameroom_bitmap);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	tekst="Wybierz kolory graczy";
	al_draw_text(font1, al_map_rgb(255,255,255), 480, 120,0, tekst.c_str());
	tekst="ABY ZAKOŃCZYĆ, NACIŚNIJ Q";
	al_draw_text(font2, al_map_rgb(255,255,255), 1050, 20,0, tekst.c_str());
	tekst="Achtung die kurve";
	al_draw_text(font3, al_map_rgb(255,22,22), 350, 10, 0, tekst.c_str());
	al_set_target_backbuffer(display);
	al_set_target_backbuffer(display);
	al_set_target_bitmap(zaciemnienie_bitmap);
	al_clear_to_color(al_map_rgba(0, 0, 0, 200));
	al_set_target_backbuffer(display);
	al_set_target_bitmap(podsumowanie_wynikow_bitmap);
	al_clear_to_color(al_map_rgba(0, 0, 0, 150));
	tekst="Achtung die kurve";
	al_draw_text(font3, al_map_rgb(255,22,22), 250, 100, 0, tekst.c_str());
	al_set_target_backbuffer(display);
	al_clear_to_color(al_map_rgb(0 ,0 , 0));

	przegranych=0;
	wybrane_kolory=0;
	int zmiennax=33;
	int zmiennay=221;
	int bok=252;

	for(int i=0;i<10;i++){
		player[i].color=-1;
	}
	for(int i=0;i<10;i++){
		switch(i){
			case 0://niebieski
				colors[i]._r = 0;
				colors[i]._g = 23;
				colors[i]._b = 155;
				break;
			case 1://zielony
				colors[i]._r = 37;
				colors[i]._g = 164;
				colors[i]._b = 40;
				break;
			case 2://szary
				colors[i]._r = 126;
				colors[i]._g = 126;
				colors[i]._b = 126;
				break;
			case 3://czerwony
				colors[i]._r = 222;
				colors[i]._g = 26;
				colors[i]._b = 26;
				break;
			case 4://zolty
				colors[i]._r = 222;
				colors[i]._g = 210;
				colors[i]._b = 23;
				break;
			case 5://fioletowy
				colors[i]._r = 124;
				colors[i]._g = 48;
				colors[i]._b = 124;
				break;
			case 6://rozowy
				colors[i]._r = 234;
				colors[i]._g = 34;
				colors[i]._b = 185;
				break;
			case 7://pomaranczowy
				colors[i]._r = 236;
				colors[i]._g = 156;
				colors[i]._b = 0;
				break;
			case 8://brazowy
				colors[i]._r = 130;
				colors[i]._g = 90;
				colors[i]._b = 30;
				break;
			case 9://blekitny
				colors[i]._r = 150;
				colors[i]._g = 110;
				colors[i]._b = 240;
			}
			colors[i].wykozystany=false;
			colors[i].animation=0;
			colors[i].size_animation=5;
			colors[i].bok=252;
			colors[i].touch=false;
			if(i==5){
				zmiennax=33;
				zmiennay=221+bok+10;
			}
			colors[i].x=zmiennax;
			colors[i].y=zmiennay;
			zmiennax=zmiennax+bok+10;
	}
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
		if(player[i].touch!=-1 || player[i].przerwa!=0){continue;}
 		al_draw_filled_circle(player[i].x, player[i].y-1, player[i].radius, al_map_rgb(colors[player[i].color]._r, colors[player[i].color]._g, colors[player[i].color]._b));
	}
	al_set_target_backbuffer(display);
	al_draw_bitmap(snakes, 20, 20, 0);
//	#################
//	WYSWIETLANIE TIMERA
	float stoper=czasomierz/60.0;
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
	
	tekst="sterowanie:";
	int py=200;
	al_draw_text(font2, al_map_rgb(255,255,255), 1170, py,0, tekst.c_str());
	
	py+=50;
	al_draw_filled_rectangle(1200, py, 1200+70, py+70,al_map_rgb(colors[player[0].color]._r , colors[player[0].color]._g, colors[player[0].color]._b));
	py+=70;
	tekst="strzałka w prawo";
	al_draw_text(font2, al_map_rgb(255,255,255), 1135, py,0, tekst.c_str());
	py+=20;
	tekst="strzałka w lewo";
	al_draw_text(font2, al_map_rgb(255,255,255), 1135, py,0, tekst.c_str());

	py+=50;
	al_draw_filled_rectangle(1200, py, 1200+70, py+70,al_map_rgb(colors[player[1].color]._r , colors[player[1].color]._g, colors[player[1].color]._b));
	py+=70;
	tekst="X";
	al_draw_text(font2, al_map_rgb(255,255,255), 1225, py,0, tekst.c_str());
	py+=20;
	tekst="Z";
	al_draw_text(font2, al_map_rgb(255,255,255), 1225, py,0, tekst.c_str());

	tekst="Aby zakończyć gre,";
	al_draw_text(font2, al_map_rgb(255,255,255), 1125, 600,0, tekst.c_str());
	tekst="naciśnij Q";
	al_draw_text(font2, al_map_rgb(255,255,255), 1170, 620,0, tekst.c_str());

}


//
// Mechanika gry
//

void aktualizuj_plansze()
{
	czas++;
	for(int i=0;i<number_of_player;i++){
		if(player[i].touch!=-1){continue;}
		
		if(player[i].przerwa_time==czasomierz){
			player[i].przerwa_time=0;
			player[i].przerwa=10;
		}
		if(player[i].przerwa>0){player[i].przerwa--;}

		player[i].x=player[i].x+player[i].step*cos(player[i].degrees);
		player[i].y=player[i].y+player[i].step*sin(player[i].degrees);
		for(int a=0;a<2*player[i].radius && player[i].touch==-1 && player[i].przerwa==0;a++){
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
							   	player[i].touch = przegranych;
							   	player[i].touch_time = czasomierz/60.0;
        					   	przegranych++;
								break;
							}
						}else if(board[iks][igrek].nrplayer!=100){
							cout<<"GRACZ "<<i<<": wiechales w kolege"<<endl;
							player[i].touch = przegranych;
							player[i].touch_time = czasomierz/60.0;
							przegranych++;
       	    	    		break;
							}else if(board[iks][igrek].nrplayer==100){
							cout<<"GRACZ "<<i<<": wjechales w sciane"<<endl;
							player[i].touch = przegranych;
							player[i].touch_time = czasomierz/60.0;
							przegranych++;
       	       	        	break;
						}
					}else{
						board[iks][igrek].nrplayer=i;
						board[iks][igrek].time=czas;
					}
				}
			if(player[i].touch!=-1){break;}
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

    clean0();

    while(!koncz_gre){	
		bool przerysuj = true;

		clean1();

		gameroom();

    	if(!wyjdz){
    		clean2();
   		}
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
           		co_robia_gracze();
            	aktualizuj_plansze();
  		       	if(licznik_fps==0){
	            	konczenie_tury();
	            }
    	        przerysuj = true;
            
        	    if(przegranych>=number_of_player){
        	   	podsumowanie_wynikow();
        	   	break;
        	   }
        	   	licznik_fps=(licznik_fps+1)%10;
        	   	czasomierz++;
           	
           	
        
        	} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        		key[ev.keyboard.keycode] = true;
        	} else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
        	    key[ev.keyboard.keycode] = false ;

       	    	if (ev.keyboard.keycode == ALLEGRO_KEY_Q) {
      	    	   break;
       	    	}
       	    	if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE || ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
       	    		menu_quit();
       	    	}
   			} else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
        	   	cursor_x = ev.mouse.x;
        	   	cursor_y = ev.mouse.y;
        	}
      		if(przerysuj && al_is_event_queue_empty(event_queue)) {
       		    przerysuj = false;

           		rysuj_plansze();

           		al_flip_display();
    		}
		}
	}
    return 0;
}
