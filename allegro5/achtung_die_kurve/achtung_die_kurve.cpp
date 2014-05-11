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

#include "run.cpp"

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
ALLEGRO_BITMAP * gameroom_player_bitmap = NULL;
ALLEGRO_BITMAP * podsumowanie_wynikow_bitmap = NULL;
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


	bool by_the_network=false;
	bool stawiam_serwer=false;
	bool ktos_postawil_serwer=false;
	int nr_gracza=-1;
	int ile_odebralem_pozycji_graczy=0;
	int ilu_gotowych=0;
	bool start=false;
	int moment_dolaczenia=-1;
	bool serwer_byl_wlaczony=false;
	string addr;//adres serwera
	bool klik_down=false;
	int wybrane_kolory=0;
	int licznik_fps=0;//%10;
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
		int touch;
		float spacetime;
	};
	type_of_player player[max_number_of_player];
	struct type{
		int nrplayer;
		int time;
	};
	type board[xpl][ypl];//+2

	 struct type_color{
	 	int _r;
	 	int _g;
	 	int _b;
	 	bool wykozystany;
	};
	type_color colors[10];
	//
// Zmienne
//
	int przegranych=0;
    bool wyjdz = false;
    int cursor_x;
    int cursor_y;
    bool cursor_pressed=false;

    int pocz_zakresu_x_0 = 200;
	int kon_zakresu_x_0 = 600;
	int pocz_zakresu_x_1 = 700;
	int kon_zakresu_x_1 = 1100;
	int pocz_zakresu_y = 200;
	int kon_zakresu_y = 700;

    
//
//Czyszczenie
//
void odbieranie_adresu(){
	cout<<"serwer: ";
	getline(cin, addr);	
}
void podsumowanie_wynikow(){

	bool przerysuj=false;

	
	stringstream ss;
	

	int przesuniecie=90;
	int przesuniecie_kwadratow=400;
	int licznik=1;
	al_set_target_bitmap(podsumowanie_wynikow_bitmap);
	for(int i=number_of_player-1;i>=0;i--){
		for(int a=0;a<number_of_player;a++){
			if(player[a].touch==i){
				ss.str("");ss.clear();
				ss<<licznik;
				string tekst =  ss.str();
				al_draw_text(font, al_map_rgb(255,255,255), 400, przesuniecie, 0, tekst.c_str());
				al_draw_filled_rectangle(450,przesuniecie+30,500,przesuniecie+60,al_map_rgb(player[a].color0,player[a].color1,player[a].color2));
				przesuniecie=przesuniecie+60;
				licznik++;
			}
		}
	}
	al_set_target_backbuffer(display);

	al_draw_bitmap(podsumowanie_wynikow_bitmap, 0, 0, 0);

	while(!wyjdz)
   	{
   		ALLEGRO_EVENT ev;
   	  	al_wait_for_event(event_queue, &ev);

    	if(ev.type == ALLEGRO_EVENT_TIMER) {
	   	   //
      	   // minęła 1/60 (1/FPS) część sekundy
       	   //
       	   przerysuj = true;

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

       	if(przerysuj && al_is_event_queue_empty(event_queue)) {
       	    przerysuj = false;
 
           	al_flip_display();
       	}
	}
}
void clean0(){
	snakes = al_create_bitmap(1080,687);
	pause_menu = al_create_bitmap(screen_w,screen_h);
	menu0_bitmap = al_create_bitmap(screen_w,screen_h);
	gameroom_bitmap = al_create_bitmap(screen_w,screen_h);
	gameroom_player_bitmap = al_create_bitmap(1310, 524);
	podsumowanie_wynikow_bitmap = al_create_bitmap(1366, 768);
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
	}
}
void skrecanie(string packet){
	service_websockets();
	stringstream ss;
	ss.str("");ss.clear();
	if(packet.substr(0,13)=="SKRECAM_LEWO_"){
		int nr_gr=(int)packet[13]-'0';
		player[nr_gr].degrees=player[nr_gr].degrees-player[nr_gr].alfa;
		player[nr_gr].lastczas=czas;
	}else if(packet.substr(0,14)=="SKRECAM_PRAWO_"){
		int nr_gr=(int)packet[14]-'0';
		player[nr_gr].degrees=player[nr_gr].degrees+player[nr_gr].alfa;
		player[nr_gr].lastczas=czas;
	}

}
void nowy_gracz(){
	service_websockets();
	number_of_player++;
	stringstream ss;
	ss.str("");ss.clear();
	ss << "number_of_player=" << number_of_player;
	cout<<"number_of_player++\n";
	send_packet(ss.str());
	service_websockets();
}
void nadanie_koloru(string packet){
	int gr=(int)packet[12]-'0';//numer gracza;
	int k=(int)packet[14]-'0';//numer koloru;
	if(player[gr].color0==-1){
		wybrane_kolory++;
	}
	player[gr].color0=colors[k]._r;
	player[gr].color1=colors[k]._g;
	player[gr].color2=colors[k]._b;
	colors[k].wykozystany=true;
}
void odbieranie_paczek(){
	service_websockets();
	string packet;
	while(receive_packet(packet)){
		cout<<"zlapalem paczke: "<<packet<<endl;
		int mnozenie_dziesiatek=1;
		if(packet.substr(0,17)=="POZYCJA_X_GRACZA_"){
			player[(int)packet[17]-'0'].x=0;
			for(int i=packet.length()-1;i>18;i--){
				player[(int)packet[17]-'0'].x=player[(int)packet[17]-'0'].x+((int)packet[i]-'0')*mnozenie_dziesiatek;
				mnozenie_dziesiatek=mnozenie_dziesiatek*10;
			}				
			ile_odebralem_pozycji_graczy++;
		}else if(packet.substr(0,17)=="POZYCJA_Y_GRACZA_"){
			player[(int)packet[17]-'0'].y=0;
			for(int i=packet.length()-1;i>18;i--){
				player[(int)packet[17]-'0'].y=player[(int)packet[17]-'0'].y+((int)packet[i]-'0')*mnozenie_dziesiatek;
				mnozenie_dziesiatek=mnozenie_dziesiatek*10;
			}
			ile_odebralem_pozycji_graczy++;
		}else if(packet=="GOTOWY"){
				ilu_gotowych++;
		}else if(packet=="NOWY GRACZ"){
       		if(nr_gracza==0){
        		nowy_gracz();
           	}
        }else if(!stawiam_serwer && packet.length()>=18 && packet.substr(0,17)=="number_of_player="){
        	ktos_postawil_serwer=true;
        	if(packet.length()==18){
        		number_of_player=(int)packet[17]-'0';
        		cout<<"number_of_player = "<<number_of_player<<"\n";
        		if(nr_gracza==-1){
        			nr_gracza=number_of_player-1;
        			cout<<"Moj nr_gracza ="<<nr_gracza<<"\n";
        		}
        	}else{
        		number_of_player=((int)packet[17]-'0')*10+((int)packet[18]-'0');
        		cout<<"number_of_player = "<<number_of_player<<"\n";
        		if(nr_gracza==-1){
        			nr_gracza=number_of_player-1;
        			cout<<"Moj nr_gracza ="<<nr_gracza<<"\n";
        		}
        	}
        }else if(!stawiam_serwer && packet=="START"){
        	start=true;
        }else if(packet.substr(0,7)=="SKRECAM"){
        	skrecanie(packet);
        }else if(packet.substr(0,12)=="KOLOR GRACZA"){
        	nadanie_koloru(packet);
        }
	}
}
void komenda_start(){
	stringstream ss;
	service_websockets();
	ss.str("");ss.clear();
	ss << "START";
	send_packet(ss.str());
	service_websockets();
}

void sprawdzenie_gotowosci(){
	cout<<"sprawdzenie_gotowosci"<<endl;
	bool wszystko_odebralem=false;
	while(true){
		string packet;
		odbieranie_paczek();
		if(!wszystko_odebralem && ile_odebralem_pozycji_graczy==2*number_of_player){
			cout<<"pozycje odebrane"<<endl;
			stringstream ss;
			ss.str(""); ss.clear();
			service_websockets();
			ss << "GOTOWY";
			send_packet(ss.str());
			service_websockets();
			wszystko_odebralem=true;
		}
		if(ilu_gotowych==number_of_player){break;}
	}
}
void clean2(){
	cout<<"jesetem w cleanie1"<<endl;
	stringstream ss;
	ss.str(""); ss.clear();


	if(!by_the_network){
		for(int i=0;i<number_of_player;i++){
			player[i].x=5;//pozycja x;
			player[i].y=5;//pozycja y;
			player[i].radius=5;//promien weza
			player[i].step=2.0;//dlugosc kroku weza
			player[i].space=10;//czas ponizej ktorego jest naliczana kolizja
			player[i].spacetime=0;//co jaki czas oczytuje czy klawisz jedt wcisnienty
			player[i].alfa=0.1;//wrazliwosc skrecania
			player[i].degrees=0;//kierunek poczatkowy gracza
			player[i].touch=-1;
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
	}else{
		for(int i=0;i<number_of_player;i++){
			player[i].radius=3;//promien weza
			player[i].step=2.0;//dlugosc kroku weza
			player[i].space=10;//czas ponizej ktorego jest naliczana kolizja
			player[i].spacetime=0;//co jaki czas oczytuje czy klawisz jedt wcisnienty
			player[i].alfa=0.1;//wrazliwosc skrecania
			player[i].degrees=0;//kierunek poczatkowy gracza
			player[i].touch=-1;
			player[i].lastczas=0;//czas ostatniego wcisniencia klawisza
			if(nr_gracza==0){
				while(player[i].x<=20+player[i].radius || player[i].y<=20+player[i].radius){
					player[i].x=random()%1072-2*player[i].radius;
					player[i].y=random()%679-2*player[i].radius;
				}
				service_websockets();
				ss.str("");ss.clear();
				ss << "POZYCJA_X_GRACZA_" <<i<<"="<<player[i].x;
				send_packet(ss.str());
				service_websockets();
				service_websockets();
				ss.str("");ss.clear();
				ss << "POZYCJA_Y_GRACZA_" <<i<<"="<<player[i].y;
				send_packet(ss.str());
				service_websockets();
				
			}
		}
		sprawdzenie_gotowosci();
	}
	przesuniecie_czasu=clock()-10000;
}
void rysowanie_kolorow(){
	al_set_target_bitmap(gameroom_player_bitmap);
	int a,b,c;
	al_clear_to_color(al_map_rgba( 0, 0, 0, 0));
	int px=5;
	int py=5;
	int bok=252;
	int przesunieciex=28;
	int przesunieciey=195;
	for(int i=0;i<10;i++){
		if(i==5){
			px=5;
			py=bok+15;
		}
		if(cursor_x>px+przesunieciex && cursor_x<px+bok+przesunieciex && cursor_y>py+przesunieciey && cursor_y<py+bok+przesunieciey){
			al_draw_filled_rectangle(px-5, py-5, px+bok+5, py+bok+5,al_map_rgb(colors[i]._r , colors[i]._g, colors[i]._b));
			if(klik_down && !cursor_pressed){
				stringstream ss;
				ss.str("");ss.clear();
				service_websockets();
				klik_down=false;
				//player[nr_gracza].color0=colors[i]._r;
				//player[nr_gracza].color1=colors[i]._g;
				//player[nr_gracza].color2=colors[i]._b;
				ss << "KOLOR GRACZA" << nr_gracza << "="<< i;
				send_packet(ss.str());
				service_websockets();

			}
		}else{
			al_draw_filled_rectangle(px, py, px+bok, py+bok,al_map_rgb(colors[i]._r , colors[i]._g, colors[i]._b));
		}
		px=px+bok+10;
	}
	al_set_target_backbuffer(display);

}

void gameroom(){

		service_websockets();
		stringstream ss;
		ss.str(""); ss.clear();

	if(stawiam_serwer){
		cout<<"OBSŁUGUJĘ SERWER\n";
		number_of_player=1;
		nr_gracza=0;
		moment_dolaczenia=0;
	}else{
		service_websockets();
		ss << "NOWY GRACZ";
		cout<<"NOWY GRACZ\n";
		send_packet(ss.str());
		service_websockets();
		moment_dolaczenia=clock();
	}
	bool przerysuj=true;
		//

	al_draw_bitmap(gameroom_bitmap, 0, 0, 0);
	al_draw_bitmap(gameroom_player_bitmap, 500, 0, 0);

	al_flip_display();
	
	while(true)
    {  	
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

       if(ev.type == ALLEGRO_EVENT_TIMER){

        	//al_draw_bitmap(gameroom_bitmap, 0, 0, 0);

            //al_flip_display();
       		przerysuj=true;

     	    rysowanie_kolorow();

     	  	odbieranie_paczek();
     	  	
     	  	if(moment_dolaczenia!=0 && clock()>=moment_dolaczenia+30){
     	  		if(!ktos_postawil_serwer){
     	  			cout<<"OBSŁUGUJĘ SERWER\n";
					number_of_player=1;
					nr_gracza=0;
					moment_dolaczenia=0;
     	  		}else{
     	  			cout<<"JESTEM ZWYKLYM UZYTKOWNIKIEM\n";
     	  			moment_dolaczenia=0;
     	  		}
     	  	}
     	    if(start){
     	    	start=false;
     	    	cout<<"zaczynamy"<<endl;
     	    	break;
     	    }


        }else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
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
           	if (nr_gracza==0 && ev.keyboard.keycode == ALLEGRO_KEY_S && wybrane_kolory==number_of_player){
           		komenda_start();
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
       	    al_draw_bitmap(gameroom_player_bitmap, 28, 200, 0);//234
          	al_flip_display();
    	}
  	}
}
int kursor_w_menu0(){
	
	if(cursor_y>pocz_zakresu_y && cursor_y<kon_zakresu_y){
		if(cursor_x>pocz_zakresu_x_1 && cursor_x<kon_zakresu_x_1){
			return 1;
		}else if(cursor_x>pocz_zakresu_x_0 && cursor_x<kon_zakresu_x_0){
			return 0;
		}else{
			return -1;
		}
	}else{
		return -1;
	}
}
void menu0(){

	al_draw_bitmap(menu0_bitmap, 0, 0, 0);
	al_flip_display();

	bool przerysuj=false;
	while(true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_TIMER) {
        	//
        	// minęła 1/60 (1/FPS) część sekundy
        	//       	
        	przerysuj = true;
        	string tekst;
        	
      		int n=kursor_w_menu0();
      		int przesuniecie=-36;
      		al_set_target_bitmap(menu0_bitmap);
       		al_clear_to_color(al_map_rgb(0, 0, 0));
       		tekst="Achtung die kurve";
			al_draw_text(font, al_map_rgb(225,100,225), 350, 50, 0, tekst.c_str());	
       		al_set_target_backbuffer(display);
       		if(n==0){
       			al_set_target_bitmap(menu0_bitmap);
       			al_draw_filled_rectangle(pocz_zakresu_x_0-5,pocz_zakresu_y-5,kon_zakresu_x_0+5,kon_zakresu_y+5,al_map_rgb(20,100,23));//129,215,120
       			tekst="Na komputerze";
       			al_draw_text(font1, al_map_rgb(255,255,255), pocz_zakresu_x_0+90, (kon_zakresu_y-pocz_zakresu_y)/2+pocz_zakresu_y+przesuniecie, 0, tekst.c_str());

       			al_set_target_backbuffer(display);
       	   	}else{
       			al_set_target_bitmap(menu0_bitmap);
       			al_draw_filled_rectangle(pocz_zakresu_x_0,pocz_zakresu_y,kon_zakresu_x_0,kon_zakresu_y,al_map_rgb(50,100,23));
       			tekst="Na komputerze";
      	 		al_draw_text(font1, al_map_rgb(255,255,255), pocz_zakresu_x_0+90, (kon_zakresu_y-pocz_zakresu_y)/2+pocz_zakresu_y+przesuniecie, 0, tekst.c_str());
       			al_set_target_backbuffer(display);
       			al_set_target_backbuffer(display);
       		}
       		if(n==1){
       			al_set_target_bitmap(menu0_bitmap);
       			al_draw_filled_rectangle(pocz_zakresu_x_1-5,pocz_zakresu_y-5,kon_zakresu_x_1+5,kon_zakresu_y+5,al_map_rgb(20,100,23));
       			tekst="Przez Sieć";
       			al_draw_text(font1, al_map_rgb(255,255,255), pocz_zakresu_x_1+90, (kon_zakresu_y-pocz_zakresu_y)/2+pocz_zakresu_y+przesuniecie, 0, tekst.c_str());
       			al_set_target_backbuffer(display);
       		}else{
       			al_set_target_bitmap(menu0_bitmap);
       			al_draw_filled_rectangle(pocz_zakresu_x_1,pocz_zakresu_y,kon_zakresu_x_1,kon_zakresu_y,al_map_rgb(50,100,23));
       			tekst="Przez Sieć";
       			al_draw_text(font1, al_map_rgb(255,255,255), pocz_zakresu_x_1+90, (kon_zakresu_y-pocz_zakresu_y)/2+pocz_zakresu_y+przesuniecie, 0, tekst.c_str());
       			al_set_target_backbuffer(display);
       		}
       		if(cursor_pressed){
       			cursor_pressed=false;
       			if(n==0){
       				break;
       			}else if(n==1){
       				int a=run_server(addr);
       				by_the_network=true;
          			if(a==1){
          				stawiam_serwer=true;
          			}else if(a==0){
          				cout<<"Nie udalo sie poloczenie z serwerem\n";
          				wyjdz=true;
          				break;
          			}else if(a==2){
          				serwer_byl_wlaczony=true;
          			}
          			gameroom();
          			break;

       			}
       		}
       	

        }else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
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
            	int a=run_server(addr);
            	if(a==1){
            		stawiam_serwer=true;
            	}else if(a==0){
            		cout<<"Nie udalo sie poloczenie z serwerem\n";
          			wyjdz=true;
          			break;
            	}else if(a==2){
          				serwer_byl_wlaczony=true;
          		}
            	gameroom();
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
        if(przerysuj && al_is_event_queue_empty(event_queue)) {
       	    przerysuj = false;
       	    al_draw_bitmap(menu0_bitmap, 0, 0, 0);
          	al_flip_display();
    	}
	}
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
	al_clear_to_color(al_map_rgba(0, 0, 0, 200));
	al_set_target_backbuffer(display);
	al_set_target_bitmap(menu0_bitmap);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	tekst="Achtung die kurve";
	al_draw_text(font, al_map_rgb(255,100,255), 350, 50, 0, tekst.c_str());
	al_set_target_backbuffer(display);
	al_set_target_bitmap(gameroom_bitmap);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	tekst="Wybierz swój kolor";
	al_draw_text(font1, al_map_rgb(255,255,255), 500, 100,0, tekst.c_str());
	al_set_target_backbuffer(display);
	al_set_target_bitmap(gameroom_player_bitmap);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_target_backbuffer(display);
	al_set_target_bitmap(podsumowanie_wynikow_bitmap);
	al_clear_to_color(al_map_rgba(0, 0, 0, 150));
	al_set_target_backbuffer(display);
	al_clear_to_color(al_map_rgb(0 ,0 , 0));

	przegranych=0;

	by_the_network=false;
	stawiam_serwer=false;
	nr_gracza=-1;
	ile_odebralem_pozycji_graczy=0;
	ilu_gotowych=0;
	start=false;
	czas=0;
	przegranych=0;
	number_of_player=2;
	ktos_postawil_serwer=false;
	for(int i=0;i<10;i++){
		player[i].color0=-1;
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
 		al_draw_filled_circle(player[i].x, player[i].y-1, player[i].radius, al_map_rgb(player[i].color0, player[i].color1, player[i].color2));
	}
	al_set_target_backbuffer(display);
	al_draw_bitmap(snakes, 20, 20, 0);
//	#################
//	WYSWIETLANIE TIMERA
	float stoper=(clock()-przesuniecie_czasu)/100000.0;
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
		if(player[i].touch!=-1){continue;}
		player[i].x=player[i].x+player[i].step*cos(player[i].degrees);
		player[i].y=player[i].y+player[i].step*sin(player[i].degrees);
		for(int a=0;a<2*player[i].radius && player[i].touch==-1;a++){
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
         					   	przegranych++;
								break;
							}
						}else if(board[iks][igrek].nrplayer!=100){
							cout<<"GRACZ "<<i<<": wiechales w kolege"<<endl;
							player[i].touch = przegranych;
							przegranych++;
        	        		break;
						}else if(board[iks][igrek].nrplayer==100){
							cout<<"GRACZ "<<i<<": wjechales w sciane"<<endl;
							player[i].touch = przegranych;
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
	if(!by_the_network){
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
	}else{
		stringstream ss;
		ss.str("");ss.clear();
		if(key[ALLEGRO_KEY_LEFT] && czas-player[0].lastczas>player[0].spacetime){
			if(czas-player[nr_gracza].lastczas>player[nr_gracza].spacetime){
				service_websockets();
				ss << "SKRECAM_LEWO_"<<nr_gracza;
				send_packet(ss.str());
				service_websockets();
			}
		}
		if(key[ALLEGRO_KEY_RIGHT] && czas-player[0].lastczas>player[0].spacetime){
			if(czas-player[nr_gracza].lastczas>player[nr_gracza].spacetime){
				service_websockets();
				ss << "SKRECAM_PRAWO_"<<nr_gracza;
				send_packet(ss.str());
				service_websockets();
			}
		}
		odbieranie_paczek();
	}
}



int main(int argc, char ** argv)
{
   	if(argc>=2){
		addr=argv[1];
		cout<<"serwer:"<<addr<<endl;
   	}else{
      	odbieranie_adresu();
    }
 	if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }

    clean0();

    	
	bool przerysuj = true;

	clean1();

	menu0();
	//	al_set_target_bitmap(snakes);
	//	al_clear_to_color(al_map_rgb(0, 0, 0));
	//	al_set_target_backbuffer(display);
	    
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
            if(licznik_fps==0){
            	co_robia_gracze();
            	aktualizuj_plansze();
            }
            przerysuj = true;
            
            if(przegranych>=number_of_player){
           	podsumowanie_wynikow();
           	by_the_network=false;
           	break;

           	licznik_fps=(licznik_fps+1)%10;
        }

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
	if(stawiam_serwer && serwer_byl_wlaczony){
		cout<<"zabijam serwer\n";
		system ("i=`ps a | pgrep server`; kill $i");
	}
    return 0;
}
