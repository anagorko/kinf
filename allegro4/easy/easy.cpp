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

	int px = xs / 2, py = ys / 2;
	int ox, oy;

	usleep(500000);

	putpixel(screen, px, py, makecol(0, 0, 255));

	while (!key[KEY_ESC]) {
		ox = px; oy = py;

		if (key[KEY_UP]) {
			py = py - 1; if (py < 0) { py = ys - 1; }
		}

		if (key[KEY_LEFT]) {
			px = px - 1; if (px < 0) { px = xs - 1; }
		}

		if (key[KEY_DOWN]) {
			py = py + 1; if (py >= ys) { py = 0; }
		}

		if (key[KEY_RIGHT]) {
			px = px + 1; if (px >= xs) { px = 0; }
		}

		if (ox != px || oy != py) {
			if (getpixel(screen, px, py) == makecol(0, 0, 255)) {
				circlefill(screen, px, py, 10, makecol(255, 0, 0));
			}

			putpixel(screen, px, py, makecol(0, 0, 255));
		}

		usleep(10000);
	}
}
END_OF_MAIN();

