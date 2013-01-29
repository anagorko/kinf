#include<allegro.h>
#include<iostream>
#include<math.h>

using namespace std;

const int xs = 640, ys = 480;

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

	putpixel(screen, 100, 100, makecol(0,255,0));

	while (!key[KEY_ESC]) {
	}
}
END_OF_MAIN();

