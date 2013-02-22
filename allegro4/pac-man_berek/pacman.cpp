#include<allegro.h>
#include<iostream>
#include<math.h>

using namespace std;

const int xs = 1366, ys = 768;

int main()
{ 
	allegro_init();
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, "" );
	install_keyboard();
	set_color_depth(24);
	set_gfx_mode( GFX_AUTODETECT, xs, ys, 0, 0);

	if (!screen) {
		cout << "Nie udalo sie otworzyc okna." << endl;
		return 1;
	}

	textprintf_centre_ex(screen, font, xs/2, ys/2, makecol(255,255,255), makecol(0,0,0), "PRESS SPACE TO START");
	
		while (!key[KEY_SPACE]) {
		usleep(20000);
		}

	
	
	textprintf_centre_ex(screen, font, xs/2, ys/2, makecol(0,255,0), makecol(0,0,0), "PAC-MAN BEREK");
	usleep(20000);	
		
	textprintf_centre_ex(screen, font, xs/2, ys/2+8, makecol(0,255,0), makecol(0,0,0), "by UndedrWorld_glider");

	usleep(800000);	

 	clear_to_color(screen, makecol(0,0,0));

	int x = xs/2+100, y = ys/2 + 100;// zmienne pacmana
	int xst = xs/2, yst = ys/2;
	int odl, wysoko;
 
	BITMAP * stwor_prawoup = load_tga("stwor3.tga", default_palette);
	BITMAP * stwor_lewoup = load_tga("stwor4.tga", default_palette);
	BITMAP * stwor_prawodol = load_tga("stwor1.tga", default_palette);
	BITMAP * stwor_lewodol = load_tga("stwor2.tga", default_palette);			
	BITMAP * pacman_lewo = load_tga("pacman.tga", default_palette);	
	BITMAP * pacman_prawo = load_tga("pacman1.tga", default_palette);	
	BITMAP * pacman_dol = load_tga("pacman2.tga", default_palette);	
	BITMAP * pacman_up = load_tga("pacman3.tga", default_palette);
	BITMAP * pacman = pacman_prawo;
	BITMAP * stwor = stwor_prawoup;

	SAMPLE * glas = load_wav( "glas.wav" );
	SAMPLE * pacmans = load_wav( "pacman.wav" );
	play_sample(pacmans, 255, 127, 1000, 1);


	while (!key[KEY_ESC]) {
		clear_to_color(screen, makecol(0,0,0));
		blit(stwor,screen,0,0,xst,yst,30,30);
		blit(pacman,screen,0,0,x,y,30,30);
		
		odl = xst - x;		
		wysoko = yst - y;

		if (key[KEY_LEFT]) {
			x = x - 5; if (x < 0) { x = xs - 1; }
			pacman = pacman_lewo;
		}
		if (key[KEY_RIGHT]) {
			x = x + 5; if (x >= xs) { x = 0; }
			pacman = pacman_prawo;
		}
		if (key[KEY_DOWN]) {
		y = y + 5; if (y >= ys) { y = 0; }
			pacman = pacman_dol;
		}
		if (key[KEY_UP]) {
			y = y - 5; if (y < 0) { y = ys - 1; }
			pacman = pacman_up;
		}
		
		if(x > xst && y < yst){
			stwor = stwor_prawoup;
		}
		if (x < xst && y < yst){
			stwor = stwor_lewoup;
		}
		if (x > xst && y > yst){
			stwor = stwor_prawodol;
		}
		if (x < xst && y > yst){
			stwor = stwor_lewodol;
		}


		if (key[KEY_A]) {
			xst = xst - 4; if (xst < 0) { xst = xs - 1; }
		}
		if (key[KEY_D]) {
			xst = xst + 4; if (xst >= xs) { xst = 0; }
		}
		if (key[KEY_S]) {
		yst = yst + 4; if (yst >= ys) { yst = 0; }
		}
		if (key[KEY_W]) {
			yst = yst - 4; if (yst < 0) { yst = ys - 1; }
		if (odl <= 30 && wysoko <= 30  ){
		
		if(xst>(x-30) && xst<(x+30) && yst>(y-30) && yst<(y+30))
		{
			allegro_message("the end.");
            		break;
		}
		else
		{

		}	
		}
			
	}
		


}	
}
END_OF_MAIN();
