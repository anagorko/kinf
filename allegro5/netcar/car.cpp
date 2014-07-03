//
// NetCar (C) Marcin Szcząchor
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include "client.h"
#include <vector>
#include <future>
#include <thread>
using namespace std;

//
// Konfiguracja gry
//

int screen_w = 1366;   // szerokość ekranu (screen width)
int screen_h = 768;   // wysokość ekranu (screen height)
const int tiles_w = 20;
const int tiles_h = 20;
const int size = 100;
const int map_w = tiles_w * size;
const int map_h = tiles_h * size;
bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze
const float FPS = 60;       // Frames Per Second
int mouse_x;
int mouse_y;
bool mouse_pressed = false;

/****************************************
 * Tu rozpoczyna się istotna część kodu *
 ****************************************/
 
//
// Struktury danych
//

class object
{
	public:
	float x;
	float y;	
};
class map
{
	public:
		float height;
		float width;
};
class camera
{
	public:
	float x;
	float y;
	camera(float new_x, float new_y){
		x = new_x;
		y = new_y;
	}
	void follow(object a){
		x = a.x;
		y = a.y;
	}
	void follow_in_borders(object a){
		
		if((a.x > screen_w/2) && (a.x < (map_w - screen_w/2)) && (a.y > screen_h/2) && (a.y < (map_h - screen_h/2))){
			x = a.x;
			y = a.y;			
		}else{
			x = a.x;
			y = a.y;
			if(a.x < screen_w/2){
				x = screen_w/2;
			}
			if(a.x > (map_w - screen_w/2)){
				x = map_w - screen_w/2;
			}
			if(a.y < screen_h/2){
				y = screen_h/2;
			}
			if(a.y > (map_h - screen_h/2)){
				y = map_h - screen_h/2;
			}
		}
	}
};
class car: public object
{
	public:
	ALLEGRO_BITMAP * image = NULL;
	string id;
	float angle;
	void draw(camera cam)
	{
		if(image == NULL)return;
		if((x > (cam.x - screen_w)) && (x < (cam.x + screen_w)) && (y > (cam.y - screen_h)) && (y < (cam.y + screen_h))){
			al_draw_rotated_bitmap (image, al_get_bitmap_width(image)/2, al_get_bitmap_height(image)/2, x - cam.x + screen_w/2, y - cam.y + screen_h/2, angle / 360.0 * 2 * 3.14159, 0);
		}	
		
	}
	car(float new_x, float new_y) {
		x = new_x;
		y = new_y;
		speed = 0;
		angle = 0;
		max_reverse_speed = 3;
		max_speed = 10;
		acceleration = 0.4;
		
	}
	car(float new_x, float new_y, float angle) {
		x = new_x;
		y = new_y;
		speed = 0;
		angle = 0;
		max_reverse_speed = 3;
		max_speed = 10;
		acceleration = 0.4;
		image = al_load_bitmap("yellow_car.png");
	}
	void accelerate(){
		if (speed + acceleration <= max_speed) {
			speed = speed + acceleration;
		}else{
			speed = max_speed;
		}
	}
	void brake(){
		if (speed - acceleration >= -max_reverse_speed) {
			speed = speed - acceleration;
		}else{
			speed = -max_reverse_speed;
		}
	}
	void left(){
		angle = angle - 2 * speed/5;
	}
	void right(){
		angle = angle + 2 * speed/5;
	}
	string generate_packet(){
		stringstream ss2;
		ss2.clear(); 
		ss2 << id << " " << x << " " << y << " " << angle;
		return ss2.str();
	}
	void calculate(){
		x = x + speed * cos(angle / 360.0 * 2 * 3.14159);
		y = y + speed * sin(angle / 360.0 * 2 * 3.14159);
		if(speed >  0){
			if (speed - 0.1 >= 0) {
				speed = speed - 0.1;
			}else{
				speed = 0;
			}
		}else{
			if (speed + 0.1 <= 0) {
				speed = speed + 0.1;
			}else{
				speed = 0;
			}
		}
	}
	private:
	float speed;
	float max_speed;
	float max_reverse_speed;
	float acceleration;
};
class tile : public object
{
	public:
	tile(float new_x, float new_y, float new_size){
		x = new_x;
		y = new_y;
		size = new_size;
	}
	tile(){}
	float size;
	void draw(camera cam)
	{
		if((x > (cam.x - screen_w/2 - size)) && (x < (cam.x + screen_w/2 + size)) && (y > (cam.y - screen_h/2 - size)) && (y < (cam.y + screen_h/2 + size))){
			al_draw_filled_rectangle (x - cam.x + screen_w/2, y - cam.y + screen_h/2, x - cam.x + screen_w/2 + size - 1, y - cam.y + screen_h/2 + size - 1, al_map_rgb(128,128,255));
		}	
		
	}
};

//
// Zmienne
//
	ALLEGRO_BITMAP * car_image = NULL;
	float x;
	float y;
	float angle = 0;
	float speed = 0;
	car autko(100, 100, 0);
	int grid [20][20];
	stringstream ss;
	vector <car> positions;
	camera kamera(screen_w/2, screen_h/2);
	tile kafelki[tiles_w][tiles_h];
	//car autko2(200, 200);
	
//
// Rysowanie planszy
//

void rysuj_plansze()
{
    al_clear_to_color(al_map_rgb(0,0,0));
	
	for(int tx = 0; tx < tiles_w; tx++){
		for(int ty = 0; ty < tiles_h; ty++){
			kafelki[tx][ty].draw(kamera);
		}
	}
	for(int i = 0; i < positions.size(); i++){
		if(positions[i].id != autko.id){
			positions[i].draw(kamera);
		}
	}
	autko.draw(kamera);
	//autko2.draw(kamera);
	kamera.follow_in_borders(autko);
}

//
// Mechanika gry
//

void aktualizuj_plansze()
{
	autko.calculate();
	ss.clear(); ss.str("");
	ss << autko.generate_packet();
	send_packet(ss.str());
	service_websockets(); // git push & pull
	string received_packets;
	while (receive_packet(received_packets))
	{
		string nick;
		ss.clear(); ss.str("");
		ss << received_packets;
		ss >> nick;
		int player_number = -1;
		for(int i = 0; i < positions.size(); i++){
			if(nick == positions[i].id){
				player_number = i;
			}
		}
		if(player_number == -1){
			player_number = positions.size();
			positions.push_back(car (100, 100, 0));
			positions.back().id = nick;		
		}
		ss >> positions[player_number].x;
		ss >> positions[player_number].y;
		ss >> positions[player_number].angle;
		
	} 
	//autko2.calculate();
}

//
// Reakcja na akcje graczy
//

void co_robia_gracze()
{
	if (key[ALLEGRO_KEY_LEFT]) {
		autko.left();
	}
	if (key[ALLEGRO_KEY_RIGHT]) {
		autko.right();
	}
	if (key[ALLEGRO_KEY_UP]) {
		autko.accelerate();
	}
	if (key[ALLEGRO_KEY_DOWN]) {
		autko.brake();
	}
	if (key[ALLEGRO_KEY_A]) {
		//autko2.left();
	}
	if (key[ALLEGRO_KEY_D]) {
		//autko2.right();
	}
	if (key[ALLEGRO_KEY_W]) {
		//autko2.accelerate();
	}
	if (key[ALLEGRO_KEY_S]) {
		//autko2.brake();
	}
}

/****************************************
 * Kod poniżej jest w miarę generyczny  *
 ****************************************/

ALLEGRO_DISPLAY_MODE disp_data;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

int init()
{
	char **xxx;
	string server_adress;
	cout << "Podaj adres serwera: ";
	cin >> server_adress;
	cout << "Podaj nick: ";
	cin >> autko.id;
	if(server_adress == "local")server_adress = "127.0.0.1";	
	if(!connect_to_server(server_adress)) {
        	cerr << "Serwer nie odpowiada" << endl;
        	return -1;
    	}
	
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

	 if (!al_init_image_addon()) {
        cerr << "Błąd podczas inicjalizacji dodatku image." << endl;
        return -1;
    }
	
	al_init_font_addon();

	 if (!al_init_ttf_addon()) {
        cerr << "Błąd podczas inicjalizacji dodatku ttf." << endl;
        return -1;
    }
  
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        cerr << "Błąd podczas inicjalizacji zegara." << endl;
        return -1;
    }

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_get_display_mode(0, &disp_data);
    screen_w = disp_data.width;
    screen_h = disp_data.height;
 
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
	al_register_event_source(event_queue, al_get_mouse_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));
	car_image = al_load_bitmap("car.png");
	x = screen_w/2;
	y = screen_h/2;
	autko.image = al_load_bitmap("yellow_car.png");
	//autko2.image = al_load_bitmap("red_car.png");
	for(int tx = 0; tx < tiles_w; tx++){
		for(int ty = 0; ty < tiles_h; ty++){
			kafelki[tx][ty].size = size;
			kafelki[tx][ty].x = tx * kafelki[tx][ty].size;
			kafelki[tx][ty].y = ty * kafelki[tx][ty].size;
		}
	}
	
  
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
                wyjdz = true;
         } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
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

            al_flip_display();
         }    
    }

    return 0;
}
