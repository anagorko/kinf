#include<allegro.h>
#include<iostream>
#include<math.h>

using namespace std;

const int N = 20;

float x[N], y[N], dx[N], dy[N];

const int xs = 1280, ys = 720;
const int r = 18;
const int speed = 4;

int main(){ 
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode( GFX_AUTODETECT, xs, ys, 0, 0);

    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    
    int ry = 2*r, rx = 2*r;

    for (int n = 0; n < N; n++) {
      x[n] = rx; y[n] = ry;
      rx = rx + 2.2*r;
      if (rx > xs - r) { rx = 2*r; ry = ry + 2.2*r; }

      dx[n] = cos(3.14159 * n / N) * speed; dy[n] = sin(3.14159 * n / N) * speed;
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
	  if ((x[i]+dx[i] - x[j]-dx[j]) * (x[i]+dx[i] - x[j]-dx[j]) +
	      (y[i]+dy[i] - y[j]-dy[j]) * (y[i]+dy[i] - y[j]-dy[j]) < 4 * r * r) {
	    // kule nr i oraz j są bliżej niż 2r od siebie

	    float tx = x[j] - x[i];
	    float ty = y[j] - y[i];

	    float px = (dx[i] * tx + dy[i] * ty) * tx / (tx * tx + ty * ty);
	    float py = (dx[i] * tx + dy[i] * ty) * ty / (tx * tx + ty * ty);

	    dx[i] = dx[i] - 2 * px;
	    dy[i] = dy[i] - 2 * py;

	    tx = x[i] - x[j];
	    ty = y[i] - y[j];

	    px = (dx[j] * tx + dy[j] * ty) * tx / (tx * tx + ty * ty);
	    py = (dx[j] * tx + dy[j] * ty) * ty / (tx * tx + ty * ty);

	    dx[j] = dx[j] - 2 * px;
	    dy[j] = dy[j] - 2 * py;

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
	  if (n == 0) {
	    circlefill(buffer, x[n], y[n], i, makecol(255-i*12,255-i*12,255-i*12));
	  } else if ((n%2) == 0) {
	    circlefill(buffer, x[n], y[n], i, makecol(255-i*12,0,0));
	  } else {
	    circlefill(buffer, x[n], y[n], i, makecol(0,0,255-i*12));
	  }
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
