#include<allegro.h>
using namespace std;
int main(){ 
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode( GFX_AUTODETECT, 1366, 768, 0, 0);
    BITMAP * buffer = NULL;
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
	BITMAP * game_over = NULL;
	BITMAP * win = NULL;
	game_over = load_bmp("game_over.bmp", default_palette);
	win = load_bmp("win.bmp", default_palette);

	int dl = 3, dl2 = 20, points = 0;
	int t[1000][2], t2[1000][2];
	int pocz = dl-1, pocz2 = dl2-1;
	int kon = 0, kon2 = 0;
	int kier = 0, kier2 = 3;
	int kulka[2];
	bool kulka_jest = true;

	kulka[0] = rand() % 1300; kulka[1] = rand() % 760;
	for(int i = 0; i < dl; i++){
	t[i][0] = 983;
	t[i][1] = 384 - i * 12;
	}
	for(int i = 0; i < dl2; i++){
	t2[i][0] = 383;
	t2[i][1] = 384 + i * 12;
	}
	while(!key[KEY_ESC]){
	for(int x = kon; x < pocz; x++){
	for(int y = x+1; y < pocz; y++){
	if(t[x][0] == t[y][0] && t[x][1] == t[y][1]){
	blit(game_over, screen, 0, 0, 0, 0, game_over->w, game_over->h);
	usleep(2000000);
	return 0;	
	}
	}}
	if(points == 30){
	blit(win, screen, 0, 0, 0, 0, win->w, win->h);
	usleep(2000000);
	return 0;}
	if(key[KEY_UP] && kier != 3){kier = 0;}
	if(key[KEY_RIGHT] && kier != 2){kier = 1;}
	if(key[KEY_LEFT] && kier != 1){kier = 2;}
	if(key[KEY_DOWN] && kier != 0){kier = 3;}
	
	t[pocz+1][1] = t[pocz][1]; t[pocz+1][0] = t[pocz][0];
	t2[pocz2+1][1] = t2[pocz2][1]; t2[pocz2+1][0] = t2[pocz2][0];
	if(t[pocz][0] - kulka[0] < 20 && t[pocz][0] - kulka[0] > -20
	&& t[pocz][1] - kulka[1] < 20 && t[pocz][1] - kulka[1] > -20){
	dl++; points++;
	kulka[0] = rand() % 1300; kulka[1] = rand() % 760;}
	else{kon++;}
	if(kon == 100){kon = 0;}
	if(kon2 == 100){kon2 = 0;}
	pocz++; pocz2++;
	if(pocz == 100){pocz = 0; t[0][0] = t[100][0]; t[0][1] = t[100][1]; }
	if(pocz2 == 100){pocz2 = 0; t2[0][0] = t2[100][0]; t2[0][1] = t2[100][1]; }

	if(kier == 0){t[pocz][1] -= 12;} if(t2[pocz2][1] - kulka[1] < 12){t2[pocz2][1] -= 12;} 
	if(kier == 1){t[pocz][0] += 12;} if(t2[pocz2][0] - kulka[0] > 12){t2[pocz2][0] += 12;}
	if(kier == 2){t[pocz][0] -= 12;} if(t2[pocz2][0] - kulka[0] < 12){t2[pocz2][0] -= 12;}
	if(kier == 3){t[pocz][1] += 12;} if(t2[pocz2][1] - kulka[1] > 12){t2[pocz2][1] += 12;}
	clear_to_color(buffer, makecol(0, 0, 0));
	if(kulka_jest){circlefill(buffer, kulka[0], kulka[1], 10, makecol(0, 0, 255));}
	for(int i = kon; i < kon + dl; i++){
	circlefill(buffer, t[i % 100][0], t[i % 100][1], 5, makecol(0, 255, 0));
	}
	textprintf_ex(buffer, font, 20, 20, makecol( 200, 200, 200 ), 50, "PUNKTY: %d", points);
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	usleep(70000);
	}

    return 0;
}
END_OF_MAIN();
