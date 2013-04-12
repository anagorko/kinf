//
// Przykładowy program wykorzystujący nasze własne funkcje 
//
//  plansza2d_init(...)
//  plansza2d_rysuj(...)
//
// z pliku nagłówkowego plansza2d.h
//

const int px = 100;
const int py = 100;

#include "plansza2d.h"

#include <iostream>
using namespace std;

int main(int argc, char ** argv)
{
    if (plansza2d_init(px * 5 + 10, py * 5 + 10) != 0)
    {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }

    ALLEGRO_COLOR plansza[px][py];
    ALLEGRO_COLOR kol0=al_map_rgb(0,0,0), kol1=al_map_rgb(156,156,156);
    for (int x = 0; x < px; x++) {
        for (int y = 0; y < py; y++) {
            plansza[x][y] = al_map_rgb(0,0,0);
        }
    }
	int x=50;
	int y=50;
	int kier=0;
    while(true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                return 0;
            }
        }

        //plansza[random() % px][random() % py] = al_map_rgb(random() % 256, random() % 256, random() % 256);
        if(color_compare(plansza[x][y],kol0)){//czrny
		plansza[x][y]=kol1;
		switch()
		x=(x+1)%100;
	}else{
		plansza[x][y]=kol0;
           	x=(x-1)%100;
	}
        plansza2d_rysuj(plansza, 5, 5);
        al_flip_display();
    }

    return 0;
}
