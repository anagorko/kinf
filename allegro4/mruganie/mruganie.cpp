#include<allegro.h>
#include<iostream>
#include<math.h>

using namespace std;

const int xs = 1336, ys = 768;

int main()
{ 
	allegro_init();
	install_keyboard();
	set_color_depth(24);
	set_gfx_mode( GFX_AUTODETECT, xs, ys, 0, 0);

	if (!screen) {
		cout << "Nie udalo sie otworzyc okna." << endl;
		return 1;
	}
int kolor[3] = { 255 , 0 , 0};
int kolejka = 1;
	
	while (!key[KEY_Z]) {
	
	if (kolejka  == 1){	// czerwony
		kolor[0] = 255;
		kolor[1] = 0;
		kolor[2] = 0;
}
	

	if (kolejka  == 2){	// zielony
		kolor[0] = 0;
		kolor[1] = 255;
		kolor[2] = 0;
}

	if (kolejka  > 2){
		kolejka = 0;
}
	kolejka += 1;

	clear_to_color(screen, makecol(0,0,0));
	textprintf_centre_ex(screen, font, xs/2, ys/2, makecol(kolor[0],kolor[1],kolor[2]), makecol(0,0,0), "Wal śmiało w klawiaturę!");
	usleep(50000);

	}
}
END_OF_MAIN();
