#include<allegro.h>
#include<iostream>
#include<math.h>

using namespace std;

const int xs = 1024, ys = 768;

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

	BITMAP * car = load_bitmap("car.tga", default_palette);

	float a = 0;
	float s = 0;
	
	float x = xs/2, y = ys/2;
		
	while (!key[KEY_ESC]) {
		rotate_sprite(screen, car, x, y, ftofix(a * 256.0 / 360.0));
		
		if (key[KEY_LEFT]) {
			a = a - 2;
		}
		if (key[KEY_RIGHT]) {
			a = a + 2;
		}
		if (key[KEY_UP]) {
			s = s + 1;
		}
		if (key[KEY_DOWN]) {
			if (s > -3) {
				s = s - 0.4;
			}
		}
		x = x + s * cos(a / 360.0 * 2 * 3.14159);
		y = y + s * sin(a / 360.0 * 2 * 3.14159);
		
		usleep(50000);
	
		clear_to_color(screen, makecol(0, 0, 0));
}
}
END_OF_MAIN();

