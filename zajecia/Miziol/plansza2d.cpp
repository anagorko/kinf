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
int t[1][3];//"0/0"=x;"O/1"=y;"0/1"=kierunek
t[0][0]=50;
t[0][1]=50;
t[0][2]=0;
    if (plansza2d_init(px * 5 + 10, py * 5 + 10) != 0)
    {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }

    ALLEGRO_COLOR plansza[px][py];
    
    for (int x = 0; x < px; x++) {
        for (int y = 0; y < py; y++) {
            plansza[x][y] = al_map_rgb(0,0,0);
        }
    }
    
    while(true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                return 0;
            }
        }

        //start mrówka

        if(t[0][2]==0){t[0][1]--;}
        if(t[0][2]==1){t[0][0]--;}
        if(t[0][2]==2){t[0][1]++;}
        if(t[0][2]==3){t[0][0]++;}

        if (color_compare(plansza[t[0][0]][t[0][1]],al_map_rgb(0,0,0))) 
            {
            t[0][2]++;
            plansza[t[0][0]][t[0][1]] = al_map_rgb(255,255,255);
            }
        else
            {
            t[0][2] += 3;
            plansza[t[0][0]][t[0][1]] = al_map_rgb(0,0,0);
            }

        t[0][0]=t[0][0]%100;
        t[0][1]=t[0][1]%100;
        t[0][2]=t[0][2]%4;

        //koniec mrówka
       
        plansza2d_rysuj(plansza, 5, 5);

        al_flip_display();
    }

    return 0;
}
