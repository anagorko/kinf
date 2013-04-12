#include <allegro.h>
#include<cstdlib>

BITMAP* bufor;

const int X = 70;
const int Y = 50;

void part(int x, int y, int r, int kolor2)
{
	circlefill(bufor, x,y,r, kolor2);
}

int main(){
	allegro_init();
	install_keyboard();
	set_color_depth( 32 );
	set_gfx_mode( GFX_AUTODETECT_WINDOWED , X*12, Y*12, 0, 0 );//moÄšĹşe byĂÂ GFX_AUTODETECT(bez: _WINDOWED); 
	clear_to_color( screen, makecol( 0, 0, 0 ) );
	BITMAP* nazwa = NULL;
	BITMAP* Pause = NULL;
	nazwa = load_bmp("game_over.bmp",default_palette);
	Pause = load_bmp("Pause.bmp" , default_palette);


	bufor = create_bitmap(X*12,Y*12);

	int t[1000][2],ta[1000][2];
	long long int pocz=10,pocza=pocz;
	int kon=0,kona=0;
	int a=rand()%10,b=rand()%10;
	char kier= 'N',kiera= 'D';
	bool czy=true;

	for (int i = 0; i < pocz+1; i++) {
		t[i][0] = 480; t[i][1] = 240 - i * 12;
		ta[i][0]= 600; ta[i][1]= 360 + i * 12;
	}

	int k1=256;
	int k2=0;
	int k3=0;

	int licznik = 0;
	int kolor1 = makecol(30,150,36);
	int kolor2 = makecol(rand()%256,rand()%256,rand()%256);

	int byl_UP = false, byl_RIGHT = false, byl_LEFT = false, byl_DOWN = false;

	while(!key[KEY_ESC]){

		licznik++;


		for (int i = 0; i < 10; i++) {
			if(key[KEY_UP] && !byl_UP){ kier = 'N'; byl_UP = true; }
			if(!key[KEY_UP]) { byl_UP = false; }

			if(key[KEY_RIGHT] && !byl_RIGHT){ kier = 'E'; byl_RIGHT = true;}
			if (!key[KEY_RIGHT]) { byl_RIGHT = false; }

			if(key[KEY_LEFT] && !byl_LEFT){ kier = 'W'; byl_LEFT = true;}
			if (!key[KEY_LEFT]) { byl_LEFT = false; }

			if(key[KEY_DOWN] && !byl_DOWN){ kier = 'S'; byl_DOWN = true; }
			if (!key[KEY_DOWN]) { byl_DOWN = false; }

			if(key[KEY_W]){ kiera = 'G';}
			if(key[KEY_D]){ kiera = 'P';}
			if(key[KEY_A]){ kiera = 'L';}
			if(key[KEY_S]){ kiera = 'D';}
 
			usleep(5000);
		}

		pocza++;
		pocz++;

		if (licznik % 5 != 0) {
			kon++; kona++;
		}

		t[pocz][0] = t[pocz-1][0];
		t[pocz][1] = t[pocz-1][1];

		ta[pocza][0] = ta[pocza-1][0];
		ta[pocza][1] = ta[pocza-1][1];


		if (kier == 'N') {
			t[pocz][1] -=12;}
		if(kier == 'S'){
			t[pocz][1] +=12;}
		if(kier == 'W'){
			t[pocz][0] -=12;}
		if(kier == 'E'){
			t[pocz][0] +=12;}


		if (kiera == 'G') {
			ta[pocza][1] -=12;}
		if(kiera == 'D'){
			ta[pocza][1] +=12;}
		if(kiera == 'L'){
			ta[pocza][0] -=12;}
		if(kiera == 'P'){
			ta[pocza][0] +=12;}

		for (int i = kon; i <= pocz; i++) {
			if (t[pocz][0] == ta[i][0] && t[pocz][1] == ta[i][1])
				kolor1 = makecol(255,0,0);
			if (t[i][0] == ta[pocza][0] && t[i][1] == ta[pocza][1])
				kolor2 = makecol(255,0,0);
		}

		clear_to_color(bufor,makecol(k1,k2,k3));
		for (long long int i = kon; i < pocz; i++) {
			if(t[pocz][0] < 0 ){t[pocz][0] = (X-1)*12;}
			if(t[pocz][0] >= X * 12){t[pocz][0]=0;}
			if(t[pocz][1] >= Y * 12){t[pocz][1]=0;}
			if(t[pocz][1] < 0 ){t[pocz][1]=(Y-1)*12;}

			rectfill(bufor, t[i][0], t[i][1], t[i][0] + 10, t[i][1] + 10, kolor1);
		}

		for (long long int i = kona; i < pocza; i++) {			
			if(ta[pocza][0] < 0){ta[pocza][0]=(X-1)*12;}
			if(ta[pocza][0] >= X * 12){ta[pocza][0]=0;}
			if(ta[pocza][1] >= Y * 12){ta[pocza][1]=0;}
			if(ta[pocza][1] < 0){ta[pocza][1]=(Y-1)*12;}


			part(ta[i][0], ta[i][1],10, kolor2); }
 
		blit(bufor,screen, 0,0,0,0,X*12,Y*12);


//.........................................................................................
		if(key[KEY_SPACE]){									//
			while(key[KEY_SPACE]){blit(Pause, screen, 0, 0, 0, 0, Pause->w, Pause->h);}	//
			while(!key[KEY_SPACE]){blit(Pause, screen, 0, 0, 0, 0, Pause->w, Pause->h);	//Pause
				if(key[KEY_ESC]){allegro_exit();return 0;}}				//
			while(key[KEY_SPACE]){blit(Pause, screen, 0, 0, 0, 0, Pause->w, Pause->h);}}	//
//...........................................................................................
		if(key[KEY_ALT] && key[KEY_F4]){allegro_exit();return 0;}
	}

	for(int i=0;i<100;i++){
		blit(nazwa, screen, 0 , 0 , 0 , 0 , nazwa->w, nazwa->h);
	}
	allegro_exit();
	return 0;
}
END_OF_MAIN();
