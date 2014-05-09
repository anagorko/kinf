//
// 2048 (C) Marcin Szcząchor
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <sstream>
#include <iostream>
using namespace std;

//
// Konfiguracja gry
//

int screen_w;   // szerokość ekranu (screen width)
int screen_h;   // wysokość ekranu (screen height)
bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze
ALLEGRO_FONT * arial = NULL;
ALLEGRO_FONT * howtoarial = NULL;
ALLEGRO_FONT * titlearial = NULL;
ALLEGRO_FONT * scorearial = NULL;
ALLEGRO_FONT * game_over_arial = NULL;
int mouse_x;
int mouse_y;
bool mouse_pressed = false;


/****************************************
 * Tu rozpoczyna się istotna część kodu *
 ****************************************/
 
//
// Struktury danych
//

class tile
{

	public:
	int number;
	int r;
	int g;
	int b;
	int animation;
	void init ()
	{
		number = 0;
	}
	void calculate ()
	{
		if(animation < 10)animation++;
		if(number > 0){
			switch (number)
			{
				case 2:
				r = 237;
				g = 227;
				b = 217;
				break;
				
				case 4:
				r = 234;
				g = 222;
				b = 198;
				break;
				
				case 8:
				r = 242;
				g = 175;
				b = 123;
				break;
				
				case 16:
				r = 244;
				g = 146;
				b = 97;
				break;
				
				case 32:
				r = 245;
				g = 124;
				b = 95;
				break;
				
				case 64:
				r = 246;
				g = 93;
				b = 61;
				break;
				
				case 128:
				r = 237;
				g = 206;
				b = 113;
				break;
				
				case 256:
				r = 236;
				g = 203;
				b = 96;
				break;
				
				case 512:
				r = 236;
				g = 200;
				b = 80;
				break;
				
				case 1024:
				r = 237;
				g = 197;
				b = 63;
				break;
				
				case 2048:
				r = 238;
				g = 194;
				b = 46;
				break;
				
				default:
				r = 62;
				g = 57;
				b = 51;
				break;
				
			}
		}
	}

};

	bool n = false;	
	bool s = false;	
	bool w = false;	
	bool e = false;	
	bool move_done = false;	
	bool no_move = false;
	bool game = false;
	bool menu = true;
	bool no_undo = true;
	float square_size;	//rozmiar planszy	
	float square_x;
	float square_y;
	float tile_size;
	float break_size;
	int score = 0;
	int highscore = 0;
	stringstream ss;
	tile tiles [4][4];
	int backup_tiles [4][4];
	int undo_backup [4][4];
	int now_backup [4][4];
	string text;
	string howto = "Join the numbers and get to the 2048 tile!";
	string title = "2048";
	string scoretxt = "Score";
	string scorenum;
	string highscoretxt = "Highscore";
	string highscorenum;
	string game_over = "Game Over";
	string newgame = "New game";
	string undo = "Undo";
	
	
	
//
// Zmienne
//

//
// Rysowanie planszy
//

void rysuj_plansze()
{
    al_clear_to_color(al_map_rgb(255,247,255));
	al_draw_filled_rounded_rectangle(square_x, square_y, square_x + square_size, square_y + square_size, square_size/50, square_size/50, al_map_rgb(188,172,159));
	

	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			al_draw_filled_rounded_rectangle(square_x + a * break_size + break_size + a * tile_size, square_y + b * break_size + break_size + b * tile_size, square_x + a * break_size + break_size + a * tile_size + tile_size, square_y + b * break_size + break_size + b * tile_size + tile_size, square_size/50, square_size/50, al_map_rgb(205,191,178));
		}	
	}

	al_draw_text(howtoarial, al_map_rgb(112,108,99), square_x/2, square_y + tile_size - break_size, ALLEGRO_ALIGN_CENTRE, howto.c_str());
	al_draw_text(titlearial, al_map_rgb(112,108,99), square_x/2, square_y - break_size * 2, ALLEGRO_ALIGN_CENTRE, title.c_str());

//
//	Rysowanie przycisku New game
//

	al_draw_filled_rounded_rectangle(break_size * 4, square_y + break_size * 5 + tile_size * 2, square_x - break_size * 4, square_y + break_size * 1 + tile_size * 3, square_size/50, square_size/50, al_map_rgb(112,108,99));
	if((mouse_pressed == true) && (mouse_x > break_size * 4) && (mouse_y > square_y + break_size * 5 + tile_size * 2) && (mouse_x <  square_x - break_size * 4) && (mouse_y < square_y + break_size * 1 + tile_size * 3)){
		al_draw_filled_rounded_rectangle(break_size * 4, square_y + break_size * 5 + tile_size * 2, square_x - break_size * 4, square_y + break_size * 1 + tile_size * 3, square_size/50, square_size/50, al_map_rgb(242,175,123));
	}
	al_draw_text(scorearial, al_map_rgb(255,247,255), square_x/2, square_y + break_size * 3 + tile_size/2 + tile_size * 2 - 15, ALLEGRO_ALIGN_CENTRE, newgame.c_str());

//
//	Rysowanie przycisku Undo
//

	al_draw_filled_rounded_rectangle(break_size * 4, square_y + break_size * 6 + tile_size * 3, square_x - break_size * 4, square_y + break_size * 2 + tile_size * 4, square_size/50, square_size/50, al_map_rgb(112,108,99));
	if((mouse_pressed == true) && (mouse_x > break_size * 4) && (mouse_y > square_y + break_size * 6 + tile_size * 3) && (mouse_x < square_x - break_size * 4) && (mouse_y <  square_y + break_size * 2 + tile_size * 4)){
		al_draw_filled_rounded_rectangle(break_size * 4, square_y + break_size * 6 + tile_size * 3, square_x - break_size * 4, square_y + break_size * 2 + tile_size * 4, square_size/50, square_size/50, al_map_rgb(242,175,123));
	}
	al_draw_text(scorearial, al_map_rgb(255,247,255), square_x/2, square_y + break_size * 4 + tile_size/2 + tile_size * 3 - 15, ALLEGRO_ALIGN_CENTRE, undo.c_str());

//
//	Rysowanie okienka Score
//	
	al_draw_filled_rounded_rectangle(square_x + square_size + break_size * 4, square_y + break_size, screen_w - break_size * 4, square_y + tile_size + break_size, square_size/50, square_size/50, al_map_rgb(112,108,99));
	al_draw_text(scorearial, al_map_rgb(255,247,255), square_x + square_size + square_x/2, square_y + break_size * 2, ALLEGRO_ALIGN_CENTRE, scoretxt.c_str());
	ss.clear();
	ss << score;
	ss >> scorenum;
	al_draw_text(scorearial, al_map_rgb(255,247,255), square_x + square_size + square_x/2, square_y + break_size + tile_size/2, ALLEGRO_ALIGN_CENTRE, scorenum.c_str());

//
//	Rysowanie okienka Highscore
//
	al_draw_filled_rounded_rectangle(square_x + square_size + break_size * 4, square_y + break_size * 2 + tile_size, screen_w - break_size * 4, square_y + tile_size * 2 + break_size * 2, square_size/50, square_size/50, al_map_rgb(112,108,99));
	al_draw_text(scorearial, al_map_rgb(255,247,255), square_x + square_size + square_x/2, square_y + break_size * 3 + tile_size, ALLEGRO_ALIGN_CENTRE, highscoretxt.c_str());
	ss.clear();
	ss << highscore;
	ss >> highscorenum;
	al_draw_text(scorearial, al_map_rgb(255,247,255), square_x + square_size + square_x/2, square_y + break_size * 2 + tile_size/2 + tile_size, ALLEGRO_ALIGN_CENTRE, highscorenum.c_str());

//
//	Rysowanie kafelków
//	
	
	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			if(tiles[a][b].number > 0){
				al_draw_filled_rounded_rectangle(square_x + a * break_size + break_size + a * tile_size + 10 * tile_size/20 - tiles[a][b].animation * tile_size/20, square_y + b * break_size + break_size + b * tile_size + 10 * tile_size/20 - tiles[a][b].animation * tile_size/20, square_x + a * break_size + break_size + a * tile_size + tile_size - 10 * tile_size/20 + tiles[a][b].animation * tile_size/20, square_y + b * break_size + break_size + b * tile_size + tile_size - 10 * tile_size/20 + tiles[a][b].animation * tile_size/20, square_size/50, square_size/50, al_map_rgb(tiles[a][b].r,tiles[a][b].g,tiles[a][b].b));
				ss.clear();
				ss << tiles[a][b].number;
				ss >> text;
				if(tiles[a][b].number > 4){
					al_draw_text(arial, al_map_rgb(255,247,255), square_x + tile_size * a + break_size * a + break_size + tile_size/2, square_y + tile_size * b + break_size * b + break_size + tile_size/2 - 25, ALLEGRO_ALIGN_CENTRE, text.c_str());
				}else{
					al_draw_text(arial, al_map_rgb(125,114,110), square_x + tile_size * a + break_size * a + break_size + tile_size/2, square_y + tile_size * b + break_size * b + break_size + tile_size/2 - 25, ALLEGRO_ALIGN_CENTRE, text.c_str());
				}
			}
		}	
	}
	if(no_move){
		al_draw_text(game_over_arial, al_map_rgb(255,247,255), screen_w/2, screen_h/2 - 40, ALLEGRO_ALIGN_CENTRE, game_over.c_str());
	}
	
}

//
// Mechanika gry
//
void make_backup(){
	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			backup_tiles[a][b] = tiles[a][b].number;
		}
	}
}

void gen_new (){
	int a;
	int b;
	a = random()%4;
	b = random()%4;
	if(tiles[a][b].number == 0){
		if(random()%2 == 0){
			tiles[a][b].number = 2;
			tiles[a][b].animation = 0;
		}else{
			tiles[a][b].number = 4;
			tiles[a][b].animation = 0;
		}
	}else{
		gen_new();
	}
}

void n_move (int a, int b)
{
	if(!((b - 1) < 0)){
		if(tiles[a][b - 1].number == tiles[a][b].number){
			score += (tiles[a][b - 1].number + tiles[a][b].number);
			tiles[a][b - 1].number += tiles[a][b].number;
			tiles[a][b].number = 0;
		}else{
			if(tiles[a][b - 1].number == 0){
				tiles[a][b - 1].number = tiles[a][b].number;
				tiles[a][b].number = 0;
				n_move(a, b - 1);
			}
		}
	}
}

void s_move (int a, int b)
{
	if(!((b + 1) > 3)){
		if(tiles[a][b + 1].number == tiles[a][b].number){
			score += (tiles[a][b + 1].number + tiles[a][b].number);
			tiles[a][b + 1].number += tiles[a][b].number;
			tiles[a][b].number = 0;
		}else{
			if(tiles[a][b + 1].number == 0){
				tiles[a][b + 1].number = tiles[a][b].number;
				tiles[a][b].number = 0;
				s_move(a, b + 1);
			}
		}
	}
}

void w_move (int a, int b)
{
	if(!((a - 1) < 0)){
		if(tiles[a - 1][b].number == tiles[a][b].number){
			score += (tiles[a - 1][b].number + tiles[a][b].number);
			tiles[a - 1][b].number += tiles[a][b].number;
			tiles[a][b].number = 0;
		}else{
			if(tiles[a - 1][b].number == 0){
				tiles[a - 1][b].number = tiles[a][b].number;
				tiles[a][b].number = 0;
				w_move(a - 1, b);
			}
		}
	}
}

void e_move (int a, int b)
{
	if(!((a + 1) > 3)){
		if(tiles[a + 1][b].number == tiles[a][b].number){
			score += (tiles[a + 1][b].number + tiles[a][b].number);
			tiles[a + 1][b].number += tiles[a][b].number;
			tiles[a][b].number = 0;
		}else{
			if(tiles[a + 1][b].number == 0){
				tiles[a + 1][b].number = tiles[a][b].number;
				tiles[a][b].number = 0;
				e_move(a + 1, b);
			}
		}
	}
}

void if_no_move(){
	no_move = true;
	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			if(!((a - 1) < 0)){
				if((tiles[a - 1][b].number == 0) || (tiles[a - 1][b].number == tiles[a][b].number)){
					no_move = false;
				}
			}
			if(!((a + 1) > 3)){
				if((tiles[a + 1][b].number == 0) || (tiles[a + 1][b].number == tiles[a][b].number)){
					no_move = false;
				}
			}
			if(!((b - 1) < 0)){
				if((tiles[a][b - 1].number == 0) || (tiles[a][b - 1].number == tiles[a][b].number)){
					no_move = false;
				}
			}
			if(!((b + 1) > 3)){
				if((tiles[a][b + 1].number == 0) || (tiles[a][b + 1].number == tiles[a][b].number)){
					no_move = false;
				}
			}
		}
	}
}

void reset()
{
	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			tiles[a][b].init();
		}
	}
	gen_new();
	gen_new();
	score = 0;
	make_backup();
}

void aktualizuj_plansze()
{
	if(n){
		n = false;
		make_backup();
		for(int b = 0; b < 4; b++){
			for(int a = 0; a < 4; a++){
				n_move(a, b);
			}
		}
	}
	if(s){
		s = false;
		make_backup();
		for(int b = 4; b >= 0; b--){
			for(int a = 0; a < 4; a++){
				s_move(a, b);
			}
		}
	}
	if(w){
		w = false;
		make_backup();
		for(int a = 0; a < 4; a++){
			for(int b = 0; b < 4; b++){
				w_move(a, b);
			}
		}
	}
	if(e){
		e = false;
		make_backup();
		for(int a = 4; a >= 0; a--){
			for(int b = 0; b < 4; b++){
				e_move(a, b);
				
			}
		}
	}
	
	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			if(!(backup_tiles[a][b] == tiles[a][b].number)){
				move_done = true;
			}
		}
	}	
	
	if(move_done){
		gen_new();
		for(int a = 0; a < 4; a++){
			for(int b = 0; b < 4; b++){
				undo_backup[a][b] = backup_tiles[a][b];
			}
		}
		make_backup();
		if(no_undo == true)no_undo = false;
	}
	move_done = false;

	if(score > highscore){
		highscore = score;
	}
	

	if((mouse_pressed == true) && (mouse_x > break_size * 4) && (mouse_y > square_y + break_size * 6 + tile_size * 3) && (mouse_x < square_x - break_size * 4) && (mouse_y <  square_y + break_size * 2 + tile_size * 4)){
		/*if(no_undo == false){
			for(int a = 0; a < 4; a++){
				for(int b = 0; b < 4; b++){
					tiles[a][b].number = undo_backup[a][b];
				}
			}
		}*/
	}

	if((mouse_pressed == true) && (mouse_x > break_size * 4) && (mouse_y > square_y + break_size * 5 + tile_size * 2) && (mouse_x <  square_x - break_size * 4) && (mouse_y < square_y + break_size * 1 + tile_size * 3)){
		reset();
	}
	
	if_no_move();	

	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			tiles[a][b].calculate();
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

ALLEGRO_DISPLAY_MODE disp_data;
ALLEGRO_DISPLAY *display;
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
	square_size = screen_h * 3/4;	
	square_x = (screen_w - square_size)/2;
	square_y = screen_h/8;
	break_size = square_size/50;
	tile_size = (square_size - 5 * break_size)/4;
	howtoarial = al_load_ttf_font("Arial.ttf", 20, 0);
	arial = al_load_ttf_font("ArialBlack.ttf", 38, 0);
	scorearial = al_load_ttf_font("ArialBlack.ttf", 20, 0);
	game_over_arial = al_load_ttf_font("ArialBlack.ttf", 38, 0);
	titlearial = al_load_ttf_font("ArialBlack.ttf", tile_size * 7/8, 0);
	

    
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
  
    al_flip_display();  
    al_start_timer(timer);

	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			tiles[a][b].init();
		}
	}

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

	gen_new();
	gen_new();
	make_backup();
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
		if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
                n = true;
            }
		if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
               	s = true;
            }
		if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                w = true;
            }
		if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                e = true;
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
