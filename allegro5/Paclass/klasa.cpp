//
// Szablon gry w Allegro 5. (C) Kółko Informatyczne Szkoły Żagle
//


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
bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze
//
// Zmienne
//


class PACMAN
{
private:

    int angle;

public:
    ALLEGRO_BITMAP *pacman;

    int x,y;

    PACMAN (){
        x = screen_w/2;
        y = screen_h/2;
        angle = 0;

    }

    void ruch()
    {
        if(key[ALLEGRO_KEY_UP]){
            y -= 2;
            angle = 270;

        } else if(key[ALLEGRO_KEY_DOWN]){
            y += 2;
            angle = 90;

        } else if(key[ALLEGRO_KEY_RIGHT]){
            x += 2;
            angle = 0;

        } else if(key[ALLEGRO_KEY_LEFT]){
            x -= 2;
            angle = 180;

        }
        if (y < 0) { y = screen_h - 1; }
        if (y > screen_h) { y = 0; }
        if (x < 0) { x = screen_w - 1; }
        if (x >= screen_w) { x = 0; }
    }

    void rysuj()
    {
    al_draw_rotated_bitmap(pacman, al_get_bitmap_width(pacman)/2, al_get_bitmap_height(pacman)/2, x, y, angle / 360.0 * 2 * 3.14159, 0);
    }















};

PACMAN pacman1;

class DUSZEK
{
public:

	int x;
	int y;
	int xcel, ycel;
	bool zmiana1;
	bool zmiana2;
	int czas;
	ALLEGRO_BITMAP* rys1;
	ALLEGRO_BITMAP* rys2;



	DUSZEK (){
		x = 100;
		y = 100;
		zmiana1 = true;
		zmiana2 = false;
		czas = 1;
		rys1 = NULL;
		rys2 = NULL;

	}







	void rysuj() {
        czas++;
        if (czas < 30){
			al_draw_bitmap(rys1,x,y,0);
        } else {
            al_draw_bitmap(rys2,x,y,0);
        } if (czas == 61){
            czas = 0;
        }

	}

    void ruch (){
        xcel = x - pacman1.x;
        ycel = y - pacman1.y;

        if (xcel < 0){
            x++;
            x++;
        } else if (xcel > 0){
            x--;
        } else if (y < 0){
            y--;
        } else if (y > 0) {
            y++;
        }
        if (y < 0) { y = screen_h - 1; }
        if (y > screen_h) { y = 0; }
        if (x < 0) { x = screen_w - 1; }
        if (x >= screen_w) { x = 0; }






    }

    void kolizja (){
        if(x>(pacman1.x -33) && x<(pacman1.x +33) && y>(pacman1.y -33) && y<(pacman1.y +33)){
            cout << "Przegrałeś rzycie"<<endl;
            exit(1);
        }



    }

};
DUSZEK duszek1;



class  MENU
{

public:
    ALLEGRO_FONT* font;
    bool start;
    bool exit;
    bool about;
    int kolejka;
    MENU (){
        font = NULL;
        start = false;
        exit = false;
        about = false;
        kolejka = 0;

    }

    void napisy()
    {

    if (kolejka == 0){
            al_draw_text(font, al_map_rgb(255,0,0), screen_w/2, screen_h/2-20, ALLEGRO_ALIGN_CENTER,"start");

    } else {
            al_draw_text(font, al_map_rgb(255,255,255), screen_w/2, screen_h/2-20, ALLEGRO_ALIGN_CENTER,"start");

    } if (kolejka == 1){
            al_draw_text(font, al_map_rgb(255,0,0), screen_w/2, screen_h/2, ALLEGRO_ALIGN_CENTER,"about");

    } else {
            al_draw_text(font, al_map_rgb(255,255,255), screen_w/2, screen_h/2, ALLEGRO_ALIGN_CENTER,"about");

    } if (kolejka == 2){
            al_draw_text(font, al_map_rgb(255,0,0), screen_w/2, screen_h/2+20, ALLEGRO_ALIGN_CENTER, "exit");

    } else {
            al_draw_text(font, al_map_rgb(255,255,255), screen_w/2, screen_h/2+20, ALLEGRO_ALIGN_CENTER, "exit");

    }

        cout << kolejka<<endl;


    }
    void sterowanie() {
        if (key[ALLEGRO_KEY_DOWN]){
            kolejka += 1;
            usleep(100000);
        } else if (key[ALLEGRO_KEY_UP]){
            kolejka -= 1;
            usleep(100000);
        }
        if (kolejka == -1){
            kolejka = 2;
            usleep(100000);
        }
        if (kolejka == 3){
            kolejka = 0;
            usleep(100000);
        }



    }
    void przyciski(){
        if (kolejka == 0 && key[ALLEGRO_KEY_ENTER]){
            start = true;
        }



    }
















};
MENU menu1;









//
// Rysowanie planszy
//

void rysuj_plansze()
{
   /* if (!menu1.start) {
        menu1.napisy();
        return;
    }*/

    al_clear_to_color(al_map_rgb(0,0,0));
    duszek1.rysuj();
    pacman1.rysuj();

}

//
// Mechanika gry
//

void aktualizuj_plansze()
{
    /*if (!menu1.start) {
        menu1.sterowanie();
        return;
    }*/

    duszek1.ruch();
    pacman1.ruch();
    duszek1.kolizja();


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

    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();


	duszek1.rys1 = al_load_bitmap("duszek1.png");
    pacman1.pacman = al_load_bitmap("pacman.png");
	duszek1.rys2 = al_load_bitmap("duszek2.png");
//	menu1.font = al_load_ttf_font("AdvoCut.ttf",16,0);
	if (duszek1.rys1 == NULL){
		cout << "nie ubało się załadować rys1."<<endl;
		exit(1);
	}
	if (duszek1.rys2 == NULL){
		cout << "nie ubało się załadować rys2."<<endl;
		exit(1);
	}
    if (pacman1.pacman == NULL){
		cout << "nie ubało się załadować pacmana."<<endl;
		exit(1);
	}
//	if (menu1.font == NULL) {
  //      cout << "nie udało się załadować fontów."<< endl;
    //    exit(1);
	//}

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

    while(!wyjdz /*|| menu1.start == true*/)
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
