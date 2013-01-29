#include<allegro.h>
#include<iostream>
#include<math.h>

using namespace std;

float x, y, dx, dy;

const int xs = 1280, ys = 720;

const int r = 40;

int main(){ 
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode( GFX_AUTODETECT, xs, ys, 0, 0);

    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    
    x = xs / 2; y = ys / 2;
    dx = 4; dy = 4;

    int kolor = makecol(255,255,255);

    while (!key[KEY_ESC]) {
      clear_to_color(buffer, makecol(0,0,0));
      
      for (int i = r; i > 0; i--) {
        circlefill(buffer, x, y, i, makecol(255-i*5,0,0));
      }
      
      if (x + dx > xs - r || x + dx < r) { dx = -dx; }
      if (y + dy > ys - r || y + dy < r) { dy = -dy; }

      vsync();
      blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
      usleep(20000);
      
      x = x + dx; y = y + dy;
    }

    return 0;
}
END_OF_MAIN();
