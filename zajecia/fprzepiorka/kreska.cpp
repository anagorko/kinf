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


	int x = 200, y = 400, c = 400, z = 200;
	int kx = 0, ky = 0, kc = 0, kz = 0;

	while (!key[KEY_ESC]) {
		circlefill( screen, x, y, 1, makecol( 40, 40, 40 ) );

		if (key[KEY_LEFT]) {
			kx = -1;
			ky = 0;
		}
		if (key[KEY_RIGHT]) {
			kx = +1;
			ky = 0;
		}
		if (key[KEY_UP]) {
			ky = -1;
			kx = 0;
		}
		if (key[KEY_DOWN]) {
			ky = +1;
			kx = 0;
		}

		x = x + kx; y = y + ky;

		circlefill( screen, c, z, 1, makecol( 225, 0, 0 ) );

		if (key[KEY_A]) {
			kc = -1;
			kz = 0;
		}
		if (key[KEY_D]) {
			kc = +1;
			kz = 0;
		}
		if (key[KEY_W]) {
			kz = -1;
			kc = 0;
		}
		if (key[KEY_S]) {
			kz = +1;
			kc = 0;
		}

		c = c + kc; z = z + kz;
		
		usleep(5000);
	}
}
END_OF_MAIN();
