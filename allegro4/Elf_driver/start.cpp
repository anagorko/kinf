#include<iostream>
#include<allegro.h>
#include<fstream>
using namespace std;

volatile long speed = 0;
void increment_speed()
{
    speed++;
}
END_OF_FUNCTION( increment_speed );
LOCK_VARIABLE( speed );
LOCK_FUNCTION( increment_speed );

int zero = 0;
int function = 1;
int train = 1, scenery = 1;
int frame = 0;

void start()
{
	fstream scene_file;
	fstream scene_inf;
	fstream komunikaty;
	char scene[10000];
	char inf[10][100];
	char komunikat[10][100];

	BITMAP * buffer = create_bitmap(1024, 768);
	BITMAP * loading = NULL;
	BITMAP * loading_end = NULL;

	BITMAP * elf = NULL;
	BITMAP * elf_open = NULL;

	BITMAP * grass = NULL;
	BITMAP * tory = NULL;

	BITMAP * tree1 = NULL;
	BITMAP * tree2 = NULL;
	BITMAP * tree3 = NULL;
	BITMAP * domek1 = NULL;
	BITMAP * domek2 = NULL;

	BITMAP * peron = NULL;
	BITMAP * dworzec = NULL;

	BITMAP * road = NULL;
	BITMAP * maluch = NULL;

	BITMAP * en57 = NULL;
	BITMAP * pasek = NULL;
	BITMAP * kom = NULL;
	BITMAP * wskaznik = NULL;
	BITMAP * wajcha = NULL;

	BITMAP * esc_tlo = NULL;
	BITMAP * esc_powr = NULL;
	BITMAP * esc_pomoc = NULL;
	BITMAP * esc_restart = NULL;
	BITMAP * esc_exit = NULL;
	BITMAP * esc_ramka = NULL;

	loading = load_bmp("images/loading.bmp", default_palette);
	loading_end = load_bmp("images/loading_end.bmp", default_palette);
	blit(loading, screen, 0, 0, zero - 1, 0, loading->w, loading->h);
	grass = load_bmp("images/grass.bmp", default_palette);
	tory = load_bmp("images/tory.bmp", default_palette);
	tree1 = load_bmp("images/tree1.bmp", default_palette);
	tree2 = load_bmp("images/tree2.bmp", default_palette);
	tree3 = load_bmp("images/tree3.bmp", default_palette);
	domek1 = load_bmp("images/domek1.bmp", default_palette);
	domek2 = load_bmp("images/domek2.bmp", default_palette);
	peron = load_bmp("images/peron.bmp", default_palette);
	dworzec = load_bmp("images/dworzec.bmp", default_palette);
	road = load_bmp("images/road.bmp", default_palette);
	maluch = load_bmp("images/maluch.bmp", default_palette);
	en57 = load_bmp("images/en57.bmp", default_palette);
	pasek = load_bmp("images/pasek.bmp", default_palette);
	kom = load_bmp("images/kom.bmp", default_palette);
	wskaznik = load_bmp("images/wskaznik.bmp", default_palette);
	wajcha = load_bmp("images/wajcha.bmp", default_palette);

	esc_tlo = load_bmp("images/esc_tlo.bmp", default_palette);
	esc_powr = load_bmp("images/esc_powr.bmp", default_palette);
	esc_pomoc = load_bmp("images/esc_pomoc.bmp", default_palette);
	esc_restart = load_bmp("images/esc_restart.bmp", default_palette);
	esc_exit = load_bmp("images/esc_exit.bmp", default_palette);
	esc_ramka = load_bmp("images/esc_ramka.bmp", default_palette);

	SAMPLE * engine = NULL;
	SAMPLE * stukot = NULL;
	engine = load_sample("sounds/engine2.wav");
	stukot = load_sample("sounds/stukot.wav");
	play_sample(engine, 255, 127, 0, 1);
	play_sample(stukot, 255, 127, 0, 1);

	if(train == 1){
		elf = load_bmp("images/elf_skm.bmp", default_palette);
		elf_open = load_bmp("images/elf_skm_open.bmp", default_palette);
	}
	if(train == 2){
		elf = load_bmp("images/elf_km.bmp", default_palette);
		elf_open = load_bmp("images/elf_km_open.bmp", default_palette);
	}
	if(train == 3){
		elf = load_bmp("images/elf_ks.bmp", default_palette);
		elf_open = load_bmp("images/elf_ks_open.bmp", default_palette);
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
	for(int i = 0; i < 10; i++){
		komunikaty.open("data/komunikaty.in", ios::in | ios::out);
		komunikaty.getline(komunikat[i], 100);
	}
	usleep(0);
	blit(loading_end, screen, 0, 0, zero, 0, loading_end->w, loading_end->h);
	usleep(500000);
	clear_to_color(screen, makecol(0, 0, 0));

	float scene_x = zero, km_x = 1500;
	float velocity = 0, acc = 0, hamowanie = 0;
	int stacja = 0, kom1 = 0;
	bool door = false, key_pressed = false, komunikat1 = false, esc = false;
	while(true){
	        frame++;
		komunikat1 = false;

		while(speed > 0){
			velocity += acc;
			if(velocity > 0){velocity -= hamowanie;}
			scene_x -= velocity;
			km_x -= 15;
			speed--;
		}
		
		if(key[KEY_UP] && acc < 0.003 && !door){acc+=0.00005;}
		if(key[KEY_DOWN] && acc > 0){acc-=0.00005;}
		if(key[KEY_SPACE] && hamowanie < 0.01 && acc < 0.0001){hamowanie+=0.0002;}
		if(!key[KEY_SPACE] && hamowanie > 0.0002){hamowanie-=0.0002;}
		if(key[KEY_D] && !key_pressed && velocity < 0.0001){
			if(!door){door = true;}
			else{door = false;}
			key_pressed = true;
			velocity = 0;
		}
		if(!key[KEY_D]){key_pressed = false;}
		if(key[KEY_ESC]){
			for(int btn = 1; true; btn = btn){
				blit(esc_tlo, buffer, 0, 0, 300, 34, esc_tlo->w, esc_tlo->h);
				blit(esc_powr, buffer, 0, 0, 310, 44, 380, 90);
				blit(esc_pomoc, buffer, 0, 0, 310, 144, 380, 90);
				blit(esc_restart, buffer, 0, 0, 310, 244, 380, 90);
				blit(esc_exit, buffer, 0, 0, 310, 344, 380, 90);
				masked_blit(esc_ramka, buffer, 0, 0, 310, 44 + (btn - 1) * 100, 380, 90);
				blit(buffer, screen, 0, 0, zero, 0, SCREEN_W, SCREEN_H);
				if(key[KEY_UP] && !key_pressed){if(btn == 1){btn = 5;} btn--; key_pressed = true;}
				if(key[KEY_DOWN] && !key_pressed){if(btn == 4){btn = 0;}btn++; key_pressed = true;}
				if(key[KEY_ENTER] && !key_pressed){
					if(btn == 1){break;}
					if(btn == 2){}
					if(btn == 3){esc = true; function = 2; break;}
					if(btn == 4){esc = true; function = 1; break;}
					key_pressed = true;
				}
				if(!key[KEY_UP] && !key[KEY_DOWN]){key_pressed = false;}
			}
		}
		if(esc){break;}
		clear_to_color(buffer, makecol(255, 255, 255));

		for(int a = 0; a < 14; a++){
		for(int b = 0; b < 10; b++){
			blit(grass, buffer, 0, 0, (int)scene_x % 100 + a * 100 - 100, 384 * 0 + b * 100, grass->w, grass->h);
		}}

		for(int a = 0; a < 13; a++){
			blit(tory, buffer, 0, 0, (int)scene_x % 100 + a * 100 - 100, 620, tory->w, tory->h);
		}

		for(int a = 0; a < 6; a++){
		for(int b = 999; b >= 0; b--){
			if(scene[a * 1000 + b] == '1'){
				masked_blit(tree1, buffer, 0, 0, scene_x + b * 100 - 200, a * 100, tree1->w, tree1->h);
			}
			if(scene[a * 1000 + b] == '2'){
				masked_blit(tree2, buffer, 0, 0, scene_x + b * 100 - 200, a * 100, tree2->w, tree2->h);
			}
			if(scene[a * 1000 + b] == '3'){
				masked_blit(tree3, buffer, 0, 0, scene_x + b * 100 - 200, a * 100, tree3->w, tree3->h);
			}
			if(scene[a * 1000 + b] == 'd'){
				masked_blit(domek1, buffer, 0, 0, scene_x + b * 100 - 200, a * 100, domek1->w, domek1->h);
			}
			if(scene[a * 1000 + b] == 'D'){
				masked_blit(domek2, buffer, 0, 0, scene_x + b * 100 - 200, a * 100, domek2->w, domek2->h);
			}
			if(scene[a * 1000 + b] == 'P'){
				masked_blit(peron, buffer, 0, 0, scene_x + b * 100 - 200, a * 100, peron->w, peron->h);
				textout_ex(buffer, font, inf[stacja], scene_x + b * 100 + 75, a * 100 + 1, makecol( 0, 0, 0 ), - 1 );
				textout_ex(buffer, font, inf[stacja], scene_x + b * 100 + 2365, a * 100 + 1, makecol( 0, 0, 0 ), - 1 );
				textout_ex(buffer, font, inf[stacja], scene_x + b * 100 + 675, a * 100 + 1, makecol( 0, 0, 0 ), - 1 );
				textout_ex(buffer, font, inf[stacja], scene_x + b * 100 + 1610, a * 100 + 1, makecol( 0, 0, 0 ), - 1 );
				stacja++;
				if(scene_x + b * 100 - 200 < 1500 && scene_x + b * 100 - 200 > 200){komunikat1 = true; kom1 = 0;}
			}
			if(scene[a * 1000 + b] == 's'){
				masked_blit(dworzec, buffer, 0, 0, scene_x + b * 100 - 200, a * 110, dworzec->w, dworzec->h);
			}
			if(scene[a * 1000 + b] == '='){
				blit(road, buffer, 0, 0, scene_x + b * 100 - 200, a * 110, road->w, road->h);
			}
			if(scene[a * 1000 + b] == 'm'){
				blit(maluch, buffer, 0, 0, scene_x + b * 100 - 200, a * 110, maluch->w, maluch->h);
			}
			if(scene[a * 1000 + b] == '#'){
				blit(tory, buffer, 0, 0, scene_x + b * 100 - 200, a * 100, tory->w, tory->h);
			}
		}}
		stacja = 0;
		masked_blit(en57, buffer, 0, 0, scene_x + km_x, 394, en57->w, en57->h);
		masked_blit(elf, buffer, 0, 0, 0, 500, elf->w, elf->h);
		if(door){masked_blit(elf_open, buffer, 0, 0, 0, 500, elf_open->w, elf_open->h);}

		masked_blit(pasek, buffer, 0, 0, 824, 0, pasek->w, pasek->h);
		masked_blit(wskaznik, buffer, 0, 0, 950, 210 - velocity * 20, wskaznik->w, wskaznik->h);
		blit(wajcha, buffer, 0, 0, 887, 350 - (int)(acc * 35000), wajcha->w, wajcha->h);
		blit(wajcha, buffer, 0, 0, 963, 350 - (int)(hamowanie * 10500), wajcha->w, wajcha->h);
		textprintf_ex(buffer, font, 20, 830, makecol( 200, 200, 200 ), 50, "%d : %d", frame, frame / 500);

		if(komunikat1){
			blit(kom, buffer, 0, 0, 10, 10, kom->w, kom->h);
			textout_ex(buffer, font, komunikat[kom1], 25, 25, makecol(0, 0, 0), -1);
		}

		blit(buffer, screen, 0, 0, zero , 0, buffer->w, buffer->h);

		adjust_sample(engine, 100 + acc * 800000 + hamowanie * 30000, 127, 100 + velocity * 75, 1);
		adjust_sample(stukot, 255, 127, velocity * 100, 1);

		speed--;
	}
	stop_sample(engine);
	stop_sample(stukot);
}

void opcje()
{
	int button = 0;
	bool key_pressed = false;
	BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
	BITMAP * tlo_menu = NULL;
	BITMAP * wyb_poc = NULL;
	BITMAP * wyb_scn = NULL;
	BITMAP * skm_button = NULL;
	BITMAP * km_button = NULL;
	BITMAP * ks_button = NULL;
	BITMAP * scn1_button = NULL;
	BITMAP * scn2_button = NULL;
	BITMAP * kolko = NULL;
	BITMAP * ramka_opcje = NULL;

	tlo_menu = load_bmp("images/tlo_menu.bmp", default_palette);
	wyb_poc = load_bmp("images/wyb_poc.bmp", default_palette);
	wyb_scn = load_bmp("images/wyb_scn.bmp", default_palette);
	skm_button = load_bmp("images/skm_button.bmp", default_palette);
	km_button = load_bmp("images/km_button.bmp", default_palette);
	ks_button = load_bmp("images/ks_button.bmp", default_palette);
	scn1_button = load_bmp("images/scn1_button.bmp", default_palette);
	scn2_button = load_bmp("images/scn2_button.bmp", default_palette);
	kolko = load_bmp("images/kolko.bmp", default_palette);
	ramka_opcje = load_bmp("images/ramka_opcje.bmp", default_palette);

	while(true){
		if(key[KEY_ESC]){function = 1; break;}
		if(key[KEY_UP] && button > 0 && !key_pressed){button--; key_pressed = true; if(button == 3){button--;}}
		if(key[KEY_DOWN] && button < 5 && !key_pressed){button++; key_pressed = true; if(button == 3){button++;}}
		if(!key[KEY_UP] && !key[KEY_DOWN]){key_pressed  = false;}
		if(key[KEY_ENTER]){
			if(button == 0){train = 1;}
			if(button == 1){train = 2;}
			if(button == 2){train = 3;}
			if(button == 4){scenery = 1;}
			if(button == 5){scenery = 2;}
		}
		clear_to_color(buffer, makecol(0, 0, 0));
		blit(tlo_menu, buffer, 0, 0, zero, 0, tlo_menu->w, tlo_menu->h);
		masked_blit(wyb_poc, buffer, 0, 0, zero + 500, 200, wyb_poc->w, wyb_poc->h);
		masked_blit(wyb_scn, buffer, 0, 0, zero + 500, 525, wyb_scn->w, wyb_scn->h);
		masked_blit(skm_button, buffer, 0, 0, zero + 600, 300, skm_button->w, skm_button->h);
		masked_blit(km_button, buffer, 0, 0, zero + 600, 375, km_button->w, km_button->h);
		masked_blit(ks_button, buffer, 0, 0, zero + 600, 450, ks_button->w, ks_button->h);
		masked_blit(scn1_button, buffer, 0, 0, zero + 600, 600, scn1_button->w, scn1_button->h);
		masked_blit(scn2_button, buffer, 0, 0, zero + 600, 675, scn2_button->w, scn2_button->h);
		masked_blit(kolko, buffer, 0, 0, zero + 870, 230 + train * 75, kolko->w, kolko->h);
		masked_blit(kolko, buffer, 0, 0, zero + 870, 530 + scenery * 75, kolko->w, kolko->h);
		masked_blit(ramka_opcje, buffer, 0, 0, zero + 600, 300 + button * 75, ramka_opcje->w, ramka_opcje->h);

		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
	function = 1;
}
void menu()
{
	int button = 0;
	bool key_pressed = false;
	BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
	BITMAP * tlo_menu = NULL;
	BITMAP * start_button = NULL;
	BITMAP * opcje_button = NULL;
	BITMAP * exit_button = NULL;
	BITMAP * ramka  = NULL;
	tlo_menu = load_bmp("images/tlo_menu.bmp", default_palette);
	start_button = load_bmp("images/start_button.bmp", default_palette);
	opcje_button = load_bmp("images/opcje_button.bmp", default_palette);
	exit_button = load_bmp("images/exit_button.bmp", default_palette);
	ramka = load_bmp("images/ramka.bmp", default_palette);
	
	while(true){
		if(key[KEY_UP] && button > 0 && !key_pressed){button--; key_pressed = true;}
		if(key[KEY_DOWN] && button < 2 && !key_pressed){button++; key_pressed = true;}
		if(!key[KEY_UP] && !key[KEY_DOWN]){ key_pressed = false;}
		if(key[KEY_ENTER]){
			if(button == 0){function = 2;}
			if(button == 1){function = 3;}
			if(button == 2){function = 4;}
			break;
		}
		clear_to_color(buffer, makecol(0, 0, 0));
		blit(tlo_menu, buffer, 0, 0, zero, 0, tlo_menu->w, tlo_menu->h);
		masked_blit(start_button, buffer, 0, 0, zero + 600, 400, start_button->w, start_button->h);
		masked_blit(opcje_button, buffer, 0, 0, zero + 600, 510, opcje_button->w, opcje_button->h);
		masked_blit(exit_button, buffer, 0, 0, zero + 600, 620, exit_button->w, exit_button->h);
		masked_blit(ramka, buffer, 0, 0, zero + 600, 400 + button *  110, ramka->w, ramka->h);
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

		usleep(5000);
	}
}

int main(){ 
    allegro_init();
    install_keyboard();
    set_color_depth( 32 );
    set_gfx_mode( GFX_AUTODETECT, 1366, 768, 0, 0 );
    clear_to_color( screen, makecol( 0, 0, 0 ) );
    zero = (SCREEN_W - 1024) / 2;

    install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, "" );
    set_volume( 255, 255 );

    install_timer();
    install_int_ex( increment_speed, BPS_TO_TIMER(100));

BITMAP * pesa = NULL;
pesa = load_bmp("images/pesa.bmp", default_palette);

if(!pesa)
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "Nie mozna zaladowac pliku!" );
    allegro_exit();
    return 0;
}
	blit(pesa, screen, 0, 0, zero, 0, pesa->w, pesa->h);
	usleep(1000000);
	while(true){
		if(function == 1){menu();}
		if(function == 2){start();}
		if(function == 3){opcje();}
		if(function == 4){break;}
	}

    allegro_exit();
    return 0;
}
END_OF_MAIN();
