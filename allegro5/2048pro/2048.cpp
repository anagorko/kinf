//
// 2048 (C) Marcin Szcząchor
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <fstream>
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
bool mouse_was_pressed = false;
bool wyjdz = false;  
bool wyjdz_was_pressed = false;


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

class button
{
	public:
	float x;
	float y;
	float cx;
	float cy;
	float rc;
	string text;
	bool pressed;
	bool active;

	void if_pressed(){
		if((mouse_pressed == true) && (mouse_x > x) && (mouse_y > y) && (mouse_x < cx) && (mouse_y < cy) && (active == true)){
			pressed = true;
		}else{
			pressed = false;
		}
	}
	void draw(){
		al_draw_filled_rounded_rectangle(x, y, cx, cy, rc, rc, al_map_rgb(112,108,99));
		if((mouse_pressed == true) && (mouse_x > x) && (mouse_y > y) && (mouse_x < cx) && (mouse_y <  cy) && (active == true)){
			al_draw_filled_rounded_rectangle(x, y, cx, cy, rc, rc, al_map_rgb(242,175,123));
		}
		if(active){
			al_draw_text(scorearial, al_map_rgb(255,247,255), x + (cx - x)/2, y + (cy - y)/2 - 15, ALLEGRO_ALIGN_CENTRE, text.c_str());
		}else{
			al_draw_text(scorearial, al_map_rgb(188,172,159), x + (cx - x)/2, y + (cy - y)/2 - 15, ALLEGRO_ALIGN_CENTRE, text.c_str());
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
	float square_x;		//x górnego rogu planszy
	float square_y;		//y górnego rogu planszy
	float tile_size;	//rozmiar kafelka
	float break_size;	//rozmiar przerwy między kafelkami
	int score = 0;		//wynik
	int highscore = 0;	//najwyższy wynik
	int undo_reload = 0;
	int undo_pause = 20;
	
	stringstream ss;
	
	tile tiles [4][4];
	int backup_tiles [4][4];
	int undo_backup [10][4][4];
	
	string text;
	string howto = "Join the numbers and get to the 2048 tile!";
	string title = "2048";
	string scoretxt = "Score";
	string scorenum;
	string highscoretxt = "Highscore";
	string highscorenum;
	string game_over = "Game Over";

	button new_game;
	button undo;
	button settings;
	button play;
	button about;
	
	
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

	new_game.draw();//	Rysowanie przycisku New game

	undo.draw();//	Rysowanie przycisku Undo

	
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
		al_draw_filled_rounded_rectangle(square_x + 4 * break_size, screen_h/2 - tile_size + break_size, square_x + square_size - 4 * break_size, screen_h/2 + tile_size - break_size, square_size/50, square_size/50, al_map_rgba(112,108,99, 200));
		al_draw_text(game_over_arial, al_map_rgb(255,247,255), screen_w/2, screen_h/2 - 30, ALLEGRO_ALIGN_CENTRE, game_over.c_str());
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
		if(random()%3 == 0){
			tiles[a][b].number = 4;
			tiles[a][b].animation = 0;
		}else{
			tiles[a][b].number = 2;
			tiles[a][b].animation = 0;
		}
	}else{
		gen_new();
	}
}

void wyjdz_fix(){
	if(wyjdz){
		if(wyjdz_was_pressed){
			wyjdz = false;
			wyjdz_was_pressed = false;
		}else{
			wyjdz_was_pressed = true;
		}
	}
}

void mouse_fix(){
	if(mouse_pressed){
		if(mouse_was_pressed){
			mouse_pressed = false;
			mouse_was_pressed = false;
		}else{
			mouse_was_pressed = true;
		}
	}
}

void n_move (int a, int b)
{
	if(!((b - 1) < 0)){
		if(tiles[a][b - 1].number == 0){
			tiles[a][b - 1].number = tiles[a][b].number;
			tiles[a][b].number = 0;
			n_move(a, b - 1);
		}
	}
}

void s_move (int a, int b)
{
	if(!((b + 1) > 3)){
		if(tiles[a][b + 1].number == 0){
			tiles[a][b + 1].number = tiles[a][b].number;
			tiles[a][b].number = 0;
			s_move(a, b + 1);
		}
	}
}

void w_move (int a, int b)
{
	if(!((a - 1) < 0)){
		if(tiles[a - 1][b].number == 0){
			tiles[a - 1][b].number = tiles[a][b].number;
			tiles[a][b].number = 0;
			w_move(a - 1, b);
		}
	}
}

void e_move (int a, int b)
{
	if(!((a + 1) > 3)){
		if(tiles[a + 1][b].number == 0){
			tiles[a + 1][b].number = tiles[a][b].number;
			tiles[a][b].number = 0;
			e_move(a + 1, b);
		}
	}
}

void vertical (int a, int w)
{
	if(w == 0){
		for(int b = 0; b < 4; b++){
			n_move(a, b);
		}
	}else{
		for(int b = 3; b >= 0; b--){
			s_move(a, b);
		}
	}

	if(w == 0){
		for(int b = 0; b < 4; b++){
			if(!((b - 1) < 0)){
				if(tiles[a][b - 1].number == tiles[a][b].number){
					score += (tiles[a][b - 1].number + tiles[a][b].number);
					tiles[a][b - 1].number += tiles[a][b].number;
					tiles[a][b].number = 0;
				}
			}
		}
	}else{
		for(int b = 3; b >= 0; b--){
			if(!((b + 1) > 3)){
				if(tiles[a][b + 1].number == tiles[a][b].number){
					score += (tiles[a][b + 1].number + tiles[a][b].number);
					tiles[a][b + 1].number += tiles[a][b].number;
					tiles[a][b].number = 0;
				}
			}
		}
	}

	if(w == 0){
		for(int b = 0; b < 4; b++){
			n_move(a, b);
		}
	}else{
		for(int b = 3; b >= 0; b--){
			s_move(a, b);
		}
	}
}

void horizontal (int b, int w)
{
	if(w == 0){
		for(int a = 0; a < 4; a++){
			w_move(a, b);
		}
	}else{
		for(int a = 3; a >= 0; a--){
			e_move(a, b);
		}
	}

	if(w == 0){
		for(int a = 0; a < 4; a++){
			if(!((a - 1) < 0)){
				if(tiles[a - 1][b].number == tiles[a][b].number){
					score += (tiles[a - 1][b].number + tiles[a][b].number);
					tiles[a - 1][b].number += tiles[a][b].number;
					tiles[a][b].number = 0;
				}
			}
		}
	}else{
		for(int a = 3; a >= 0; a--){
			if(!((a + 1) > 3)){
				if(tiles[a + 1][b].number == tiles[a][b].number){
					score += (tiles[a + 1][b].number + tiles[a][b].number);
					tiles[a + 1][b].number += tiles[a][b].number;
					tiles[a][b].number = 0;
				}
			}
		}
	}

	if(w == 0){
		for(int a = 0; a < 4; a++){
			w_move(a, b);
		}
	}else{
		for(int a = 3; a >= 0; a--){
			e_move(a, b);
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
	make_backup();

	new_game.if_pressed();
	undo.if_pressed();

	if(n){
		n = false;
		make_backup();
		for(int a = 0; a < 4; a++){
			vertical(a, 0);
		}
	}
	if(s){
		s = false;
		make_backup();
		for(int a = 0; a < 4; a++){
			vertical(a, 1);
		}
	}
	if(w){
		w = false;
		make_backup();
		for(int b = 0; b < 4; b++){
			horizontal(b, 0);
		}
	}
	if(e){
		e = false;
		make_backup();
		for(int b = 0; b < 4; b++){
			horizontal(b, 1);
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
		for(int i = 8; i >= 0; i--){
			for(int a = 0; a < 4; a++){
				for(int b = 0; b < 4; b++){
					  undo_backup[i + 1][a][b] = undo_backup[i][a][b];
				}
			}
		}
		for(int a = 0; a < 4; a++){
			for(int b = 0; b < 4; b++){
				undo_backup[0][a][b] = tiles[a][b].number;
			}
		}
		if(no_undo == true)no_undo = false;
		
		if(undo_reload < undo_pause)undo_reload++;
		if(undo_reload == undo_pause)undo.active = true;
		else undo.active = false;
	}
	move_done = false;
	
	ifstream highscore_in(".highscore.txt");
	highscore_in >> highscore;
	highscore_in.close();
	if(score > highscore){
		highscore = score;
		ofstream highscore_out(".highscore.txt");
		highscore_out << score;
		highscore_out.close();
	}
	

	if(undo.pressed && no_undo == false){
			for(int a = 0; a < 4; a++){
				for(int b = 0; b < 4; b++){
					tiles[a][b].number = undo_backup[1][a][b];
				}
			}
			for(int i = 1; i < 10; i++){
				for(int a = 0; a < 4; a++){
					for(int b = 0; b < 4; b++){
						 undo_backup[i - 1][a][b] = undo_backup[i][a][b];
					}
				}
			}
			for(int a = 0; a < 4; a++){
				for(int b = 0; b < 4; b++){
					undo_backup[9][a][b] = 0;
				}
			}
			undo_reload = 0;
			undo.active = false;
	}

	if(new_game.pressed == true){
		reset();
	}
	
	if_no_move();	

	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			tiles[a][b].calculate();
		}
	}	
	
	mouse_fix();
	
}

//
// Reakcja na akcje graczy
//

void co_robia_gracze()
{
}

void rysuj_menu(){
	 al_clear_to_color(al_map_rgb(255,247,255));
	play.draw();
	settings.draw();
	about.draw();
}

void aktualizuj_menu(){
	mouse_fix();
	play.if_pressed();
	settings.if_pressed();
	about.if_pressed();
	if(play.pressed){
		menu = false;
		game = true;
	}
}

void rysuj_ekran(){
	if(game && !menu)rysuj_plansze();
	if(menu && !game)rysuj_menu();
}

/****************************************
 * Kod poniżej jest w miarę generyczny  *
 ****************************************/

void init_game_buttons (){

//
// Inicjalizacja przycisku New game
//
	new_game.x = break_size * 4;
	new_game.y = square_y + break_size * 5 + tile_size * 2;
	new_game.cx = square_x - break_size * 4;
	new_game.cy = square_y + break_size * 1 + tile_size * 3;
	new_game.rc = square_size/50;
	new_game.text = "New game";
	new_game.pressed = false;
	new_game.active = true;
//
// Inicjalizacja przycisku Undo
//
	undo.x = break_size * 4;
	undo.y = square_y + break_size * 6 + tile_size * 3;
	undo.cx = square_x - break_size * 4;
	undo.cy = square_y + break_size * 2 + tile_size * 4;
	undo.rc = square_size/50;
	undo.text = "Undo";
	undo.pressed = false;
	undo.active = false;
}

void init_menu_buttons(){

//
// Inicjalizacja przycisku Play
//
	play.x = screen_w/2 - (square_x + 8 * break_size)/2;
	play.y = screen_h/2 - tile_size/2 + break_size * 2;
	play.cx = screen_w/2 + (square_x + 8 * break_size)/2;
	play.cy = screen_h/2 + tile_size/2 - break_size * 2;
	play.rc = square_size/50;
	play.text = "Play";
	play.pressed = false;
	play.active = true;

//
// Inicjalizacja przycisku Settings
//
	settings.x = screen_w/2 - (square_x + 8 * break_size)/2;
	settings.y = screen_h/2 + tile_size/2 - break_size;
	settings.cx = screen_w/2 + (square_x + 8 * break_size)/2;
	settings.cy = screen_h/2 + tile_size/2 - break_size * 5 + tile_size;
	settings.rc = square_size/50;
	settings.text = "Settings";
	settings.pressed = false;
	settings.active = true;


//
// Inicjalizacja przycisku About
//
	about.x = screen_w/2 - (square_x + 8 * break_size)/2;
	about.y = screen_h/2 + tile_size/2 - break_size * 4 + tile_size;
	about.cx = screen_w/2 + (square_x + 8 * break_size)/2;
	about.cy = screen_h/2 + tile_size/2 - break_size * 8 + 2 * tile_size;
	about.rc = square_size/50;
	about.text = "About";
	about.pressed = false;
	about.active = true;

}

 
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
	for(int i = 9; i >= 0; i--){
			for(int a = 0; a < 4; a++){
				for(int b = 0; b < 4; b++){
					undo_backup[i][a][b] = 0;
				}
			}
	}
	init_game_buttons();
	init_menu_buttons();

    
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

	gen_new();
	gen_new();
	make_backup();
    //
    // Event loop - główna pętla programu
    //
        
    for(;;)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            //
            // minęła 1/60 (1/FPS) część sekundy
            //
            przerysuj = true;

	if(game && !menu){
            co_robia_gracze();

            aktualizuj_plansze();
	}
	
	if(menu && !game){
		aktualizuj_menu();
		rysuj_menu();
	}
		

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
	
            rysuj_ekran();

            al_flip_display();
		
	}
         
	wyjdz_fix();
	if(wyjdz && menu && !game)break;
		if(wyjdz && !menu && game){
			menu = true;
			game = false;
		}    
	}

    return 0;
}
