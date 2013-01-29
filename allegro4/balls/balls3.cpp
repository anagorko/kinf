#include<allegro.h>
#include<iostream>
#include<math.h>

using namespace std;

const int N = 40;

float x[N], y[N], dx[N], dy[N];

const int xs = 1280, ys = 720;

const int r = 20;

int main(){ 
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode( GFX_AUTODETECT, xs, ys, 0, 0);

    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    
    for (int n = 0; n < N; n++) {
      x[n] = r + n * 3 * r; y[n] = ys / 2;
      dx[n] = cos(3.14159 * n / N) * 4; dy[n] = sin(3.14159 * n / N) * 4;
    }

    while (!key[KEY_ESC]) {
      // kolizje z brzegiem ekranu
      for (int n = 0; n < N; n++) {      
	if (x[n] + dx[n] > xs - r || x[n] + dx[n] < r) { dx[n] = -dx[n]; }
	if (y[n] + dy[n] > ys - r || y[n] + dy[n] < r) { dy[n] = -dy[n]; }
      }

      // kolizje pomiędzy kulami
      for (int i = 0; i < N; i++) {
	for (int j = i + 1; j < N; j++) {
	  if ((x[i] - x[j]) * (x[i] - x[j]) +
	      (y[i] - y[j]) * (y[i] - y[j]) < 4 * r * r) {
	    // kule nr i oraz j są bliżej niż 2r od siebie
	    // zmieniamy im kierunki na przeciwne
	    // z arbitralnie ustaloną prędkością

	    dx[i] = 2*(x[i] - x[j])/r;
	    dy[i] = 2*(y[i] - y[j])/r;

	    dx[j] = -dx[i];
	    dy[j] = -dy[i];

	    // ten model odbicia jest nierealistyczny
	    // dlaczego? widzisz to?
	  }
	}
      }

      // przesunięcie kul
      for (int n = 0; n < N; n++) {
	x[n] = x[n] + dx[n]; y[n] = y[n] + dy[n];
      }

      // rysowanie kul
      clear_to_color(buffer, makecol(0,0,0));      
      for (int n = 0; n < N; n++) {
	for (int i = r; i > 0; i--) {
	  circlefill(buffer, x[n], y[n], i, makecol(255-i*12,0,0));
	}
      }

      // wyświetlenie (double buffering)
      vsync();
      blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
      usleep(20000);      
    }

    return 0;
}
END_OF_MAIN();
