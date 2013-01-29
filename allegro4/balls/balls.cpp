#include<allegro.h>
#include<iostream>
#include<math.h>

using namespace std;

const int N = 3;

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
      x[n] = xs / 2; y[n] = ys / 2;
      dx[n] = cos(3.14159 * n / N) * 4; dy[n] = sin(3.14159 * n / N) * 4;
    }

    int kolor = makecol(255,255,255);

    while (!key[KEY_ESC]) {
      // kolizje z brzegiem ekranu
      for (int n = 0; n < N; n++) {      
	if (x[n] + dx[n] > xs - r || x[n] + dx[n] < r) { dx[n] = -dx[n]; }
	if (y[n] + dy[n] > ys - r || y[n] + dy[n] < r) { dy[n] = -dy[n]; }
      }

      // przesunięcie kul
      for (int n = 0; n < N; n++) {
	x[n] = x[n] + dx[n]; y[n] = y[n] + dy[n];
      }

      // rysowanie kul
      clear_to_color(buffer, makecol(0,0,0));      
      for (int n = 0; n < N; n++) {
	for (int i = r; i > 0; i--) {
	  circlefill(buffer, x[n], y[n], i, makecol(255-i*5,0,0));
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
