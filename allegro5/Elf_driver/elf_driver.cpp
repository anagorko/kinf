#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
using namespace std;

const int screen_w = 1024;
const int screen_h = 768;

int zero = 0;
int func = 1;
int train = 1, scenery = 1;

float scene_x;
float velocity, acc, hamowanie;
int stacja;
bool door, key_pressed;

int button;
bool wyjdz = false, tak = true;

bool key[ALLEGRO_KEY_MAX];
const float FPS = 60;

fstream scene_file;
fstream scene_inf;
char scene[10000];
char inf[10][100];

	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_DISPLAY_MODE   disp_data;
	ALLEGRO_EVENT_QUEUE * event_queue = NULL;
	ALLEGRO_TIMER * timer = NULL;

	ALLEGRO_BITMAP * pesa = NULL;

	ALLEGRO_BITMAP * loading = NULL;
	ALLEGRO_BITMAP * loading_end = NULL;
	ALLEGRO_BITMAP * elf = NULL;
	ALLEGRO_BITMAP * elf_open = NULL;
	ALLEGRO_BITMAP * grass = NULL;
	ALLEGRO_BITMAP * tory = NULL;
	ALLEGRO_BITMAP * tree1 = NULL;
	ALLEGRO_BITMAP * tree2 = NULL;
	ALLEGRO_BITMAP * tree3 = NULL;
	ALLEGRO_BITMAP * domek1 = NULL;
	ALLEGRO_BITMAP * domek2 = NULL;
	ALLEGRO_BITMAP * peron = NULL;
	ALLEGRO_BITMAP * road = NULL;
	ALLEGRO_BITMAP * maluch = NULL;
	ALLEGRO_BITMAP * en57 = NULL;
	ALLEGRO_BITMAP * pasek = NULL;
	ALLEGRO_BITMAP * kom = NULL;
	ALLEGRO_BITMAP * wskaznik = NULL;
	ALLEGRO_BITMAP * wajcha = NULL;

	ALLEGRO_BITMAP * tlo_menu = NULL;
	ALLEGRO_BITMAP * wyb_poc = NULL;
	ALLEGRO_BITMAP * wyb_scn = NULL;
	ALLEGRO_BITMAP * skm_button = NULL;
	ALLEGRO_BITMAP * km_button = NULL;
	ALLEGRO_BITMAP * ks_button = NULL;
	ALLEGRO_BITMAP * scn1_button = NULL;
	ALLEGRO_BITMAP * scn2_button = NULL;
	ALLEGRO_BITMAP * kolko = NULL;
	ALLEGRO_BITMAP * ramka_opcje = NULL;

	ALLEGRO_BITMAP * start_button = NULL;
	ALLEGRO_BITMAP * opcje_button = NULL;
	ALLEGRO_BITMAP * exit_button = NULL;
	ALLEGRO_BITMAP * ramka  = NULL;

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

    if (!al_init_image_addon()) {
	al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", 
	NULL, ALLEGRO_MESSAGEBOX_ERROR);
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

void prepare_start()
{
	loading = al_load_bitmap("images/loading.png");
	loading_end = al_load_bitmap("images/loading_end.png");
	al_draw_bitmap(loading, zero - 1, 0, 0);
	grass = al_load_bitmap("images/grass.png");
	tory = al_load_bitmap("images/tory.png");
	tree1 = al_load_bitmap("images/tree1.png");
	tree2 = al_load_bitmap("images/tree2.png");
	tree3 = al_load_bitmap("images/tree3.png");
	domek1 = al_load_bitmap("images/domek1.png");
	domek2 = al_load_bitmap("images/domek2.png");
	peron = al_load_bitmap("images/peron.png");
	road = al_load_bitmap("images/road.png");
	maluch = al_load_bitmap("images/maluch.png");
	en57 = al_load_bitmap("images/en57.png");
	pasek = al_load_bitmap("images/pasek.png");
	kom = al_load_bitmap("images/kom.png");
	wskaznik = al_load_bitmap("images/wskaznik.png");
	wajcha = al_load_bitmap("images/wajcha.png");

	//SAMPLE * engine = NULL;
	//SAMPLE * stukot = NULL;
	//engine = load_sample("sounds/engine2.wav");
	//stukot = load_sample("sounds/stukot.wav");
	//play_sample(engine, 255, 127, 0, 1);
	//play_sample(stukot, 255, 127, 0, 1);

	if(train == 1){
		elf = al_load_bitmap("images/elf_skm.png");
		elf_open = al_load_bitmap("images/elf_skm_open.png");
	}
	if(train == 2){
		elf = al_load_bitmap("images/elf_km.png");
		elf_open = al_load_bitmap("images/elf_km_open.png");
	}
	if(train == 3){
		elf = al_load_bitmap("images/elf_ks.png");
		elf_open = al_load_bitmap("images/elf_ks_open.png");
	}
	if(scenery == 1){
		scene_file.open("scenery/scn1.sc", ios::in | ios::out);
		scene_file.read(scene, 10000);
		scene_inf.open("scenery/scn1.in", ios::in | ios::out);
		for(int i = 0; i < 10; i++){
			scene_inf.getline(inf[i], 100);
		}
	}
	if(scenery == 2){
		scene_file.open("scenery/scn2.sc", ios::in | ios::out);
		scene_file.read(scene, 10000);
		scene_inf.open("scenery/scn2.in", ios::in | ios::out);
		for(int i = 0; i < 10; i++){
			scene_inf.getline(inf[i], 100);
		}
	}
	usleep(1000000);
	al_draw_bitmap(loading_end, zero, 0, 0);
	usleep(500000);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	scene_x = zero;
	velocity = 0, acc = 0, hamowanie = 0;
	stacja = 0;
	door = false;
	key_pressed = false;
}
void start()
{
	velocity += acc;
	if(velocity > 0){velocity -= hamowanie;}
	scene_x -= velocity;

	if(key[ALLEGRO_KEY_ESCAPE]){func = 1;}
	if(key[ALLEGRO_KEY_UP] && acc < 0.003 && !door){acc+=0.00005;}
	if(key[ALLEGRO_KEY_DOWN] && acc > 0){acc-=0.00005;}
	if(key[ALLEGRO_KEY_SPACE] && hamowanie < 0.01 && acc < 0.0001){hamowanie+=0.0002;}
	if(!key[ALLEGRO_KEY_SPACE] && hamowanie > 0.0002){hamowanie-=0.0002;}
	if(key[ALLEGRO_KEY_D] && !key_pressed && velocity < 0.0001){
		if(!door){door = true;}
		else{door = false;}
		key_pressed = true;
	}
	if(!key[ALLEGRO_KEY_D]){key_pressed = false;}
}
void start_1()
{

	al_clear_to_color(al_map_rgb(0, 0, 0));

	for(int a = 0; a < 15; a++){
	for(int b = 0; b < 10; b++){
		al_draw_bitmap(grass, (int)scene_x % 100 + a * 100 - 100, 384 * 0 + b * 100, 0);
	}}

	for(int a = 0; a < 13; a++){
		al_draw_bitmap(tory, (int)scene_x % 100 + a * 100 - 100, 620, 0);
	}

	for(int a = 0; a < 6; a++){
	for(int b = 999; b >= 0; b--){
		if(scene[a * 1000 + b] == '1'){
			al_draw_bitmap(tree1, zero + scene_x +b * 100 - 200, a * 100, 0);
		}
		if(scene[a * 1000 + b] == '2'){
			al_draw_bitmap(tree2, zero + scene_x +b * 100 - 200, a * 100, 0);
		}
		if(scene[a * 1000 + b] == '3'){
			al_draw_bitmap(tree3, zero + scene_x +b * 100 - 200, a * 100, 0);
		}
		if(scene[a * 1000 + b] == 'd'){
			al_draw_bitmap(domek1, zero + scene_x +b * 100 - 200, a * 100, 0);
		}
		if(scene[a * 1000 + b] == 'D'){
			al_draw_bitmap(domek2, zero + scene_x +b * 100 - 200, a * 100, 0);
		}
		if(scene[a * 1000 + b] == 'P'){
			al_draw_bitmap(peron, zero + scene_x +b * 100 - 200, 500, 0);
			//textout_ex(buffer, font, inf[stacja], zero + scene_x +b * 100 + 75, 501, makecol( 0, 0, 0 ), - 1 );
			//textout_ex(buffer, font, inf[stacja], zero + scene_x +b * 100 + 2365, 501, makecol( 0, 0, 0 ), - 1 );
			stacja++;
		}
		if(scene[a * 1000 + b] == '='){
			al_draw_bitmap(road, zero + scene_x +b * 100 - 200, a * 110, 0);
		}
		if(scene[a * 1000 + b] == 'm'){
			al_draw_bitmap(maluch, zero + scene_x +b * 100 - 200, a * 110, 0);
		}
		if(scene[a * 1000 + b] == '#'){
			al_draw_bitmap(tory, zero + scene_x +b * 100 - 200, a * 100, 0);
		}
		if(scene[a * 1000 + b] == 'K'){
			al_draw_bitmap(en57, zero + scene_x +b * 100 - 200, 394, 0);
		}
	}}
	stacja = 0;
	al_draw_bitmap(elf, 0, 500, 0);
	if(door){al_draw_bitmap(elf_open, 0, 500, 0);}

	al_draw_bitmap(pasek, zero + 824 + 140, 0, 0);
	al_draw_bitmap(wskaznik, zero + 950 + 140, 210 - velocity * 20, 0);
	al_draw_bitmap(wajcha, zero + 887 + 140, 350 - (int)(acc * 35000), 0);
	al_draw_bitmap(wajcha, zero + 963 + 140, 350 - (int)(hamowanie * 10500), 0);

	//adjust_sample(engine, 100 + acc * 800000 + hamowanie * 30000, 127, 100 + velocity * 75, 1);
	//adjust_sample(stukot, 255, 127, velocity * 100, 1);

	//stop_sample(engine);
	//stop_sample(stukot);

	al_set_target_backbuffer(display);
}

void opcje()
{
	if(key[ALLEGRO_KEY_ESCAPE]){func = 1;}
	if(key[ALLEGRO_KEY_UP] && button > 0 && !key_pressed){button--; key_pressed = true; if(button == 3){button--;}}
	if(key[ALLEGRO_KEY_DOWN] && button < 5 && !key_pressed){button++; key_pressed = true; if(button == 3){button++;}}
	if(!key[ALLEGRO_KEY_UP] && !key[ALLEGRO_KEY_DOWN]){key_pressed  = false;}
	if(key[ALLEGRO_KEY_ENTER]){
		if(button == 0){train = 1;}
		if(button == 1){train = 2;}
		if(button == 2){train = 3;}
		if(button == 4){scenery = 1;}
		if(button == 5){scenery = 2;}
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(tlo_menu, zero, 0, 0);
	al_draw_bitmap(wyb_poc, zero + 500, 200, 0);
	al_draw_bitmap(wyb_scn, zero + 500, 525, 0);
	al_draw_bitmap(skm_button, zero + 600, 300, 0);
	al_draw_bitmap(km_button, zero + 600, 375, 0);
	al_draw_bitmap(ks_button, zero + 600, 450, 0);
	al_draw_bitmap(scn1_button, zero + 600, 600, 0);
	al_draw_bitmap(scn2_button, zero + 600, 675, 0);
	al_draw_bitmap(kolko, zero + 870, 230 + train * 75, 0);
	al_draw_bitmap(kolko, zero + 870, 530 + scenery * 75, 0);
	al_draw_bitmap(ramka_opcje, zero + 600, 300 + button * 75, 0);

	al_set_target_backbuffer(display);
}
void prepare_menu()
{
	button = 0;
	key_pressed = false;

	tlo_menu = al_load_bitmap("images/tlo_menu.png");
	start_button = al_load_bitmap("images/start_button.png");
	opcje_button = al_load_bitmap("images/opcje_button.png");
	exit_button = al_load_bitmap("images/exit_button.png");
	ramka = al_load_bitmap("images/ramka.png");
	wyb_poc = al_load_bitmap("images/wyb_poc.png");
	wyb_scn = al_load_bitmap("images/wyb_scn.png");
	skm_button = al_load_bitmap("images/skm_button.png");
	km_button = al_load_bitmap("images/km_button.png");
	ks_button = al_load_bitmap("images/ks_button.png");
	scn1_button = al_load_bitmap("images/scn1_button.png");
	scn2_button = al_load_bitmap("images/scn2_button.png");
	kolko = al_load_bitmap("images/kolko.png");
	ramka_opcje = al_load_bitmap("images/ramka_opcje.png");
}
void menu()
{
	
	if(key[ALLEGRO_KEY_UP] && button > 0 && !key_pressed){button--; key_pressed = true;}
	if(key[ALLEGRO_KEY_DOWN] && button < 2 && !key_pressed){button++; key_pressed = true;}
	if(!key[ALLEGRO_KEY_UP] && !key[ALLEGRO_KEY_DOWN]){ key_pressed = false;}
	if(key[ALLEGRO_KEY_ENTER]){
		if(button == 0){func = 2;prepare_start();}
		if(button == 1){func = 3;}
		if(button == 2){func = 4;}
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(tlo_menu, zero, 0, 0);
	al_draw_bitmap(start_button, zero + 600, 400, 0);
	al_draw_bitmap(opcje_button, zero + 600, 510, 0);
	al_draw_bitmap(exit_button, zero + 600, 620, 0);
	al_draw_bitmap(ramka, zero + 600, 400 + button *  110, 0);
}

int main(int argc, char ** argv){ 

    if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    zero = 140;

    //display = al_create_display(1024,768);

    //install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, "" );
    //set_volume( 255, 255 );

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(1366, 768);

	pesa = al_load_bitmap("images/pesa.png");
	al_flip_display();

	al_draw_bitmap(pesa, zero, 0, 0);
	al_flip_display();
	usleep(1000000);
	prepare_menu();
	prepare_start();
	func = 1;

	while(!wyjdz){

		ALLEGRO_EVENT ev;
        	al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			tak = true;

			if(func == 2){start();}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			key[ev.keyboard.keycode] = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            		key[ev.keyboard.keycode] = false;

            	//if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                //	wyjdz = true;
            	//}
		}
		if(tak && al_is_event_queue_empty(event_queue)) {
			tak = false;

			if(func == 1){menu();}
			if(func == 2){start_1();}
			if(func == 3){opcje();}
			if(func == 4){break;}

			al_flip_display();
		}

	}
    return 0;
}
