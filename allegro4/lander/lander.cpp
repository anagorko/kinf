#include<allegro.h>
#include<iostream>
#include<math.h>

using namespace std;

const int xs = 1366;
const int ys = 768;

int main(){ 
	srand(getpid());
	
	allegro_init();
	install_keyboard();
	set_color_depth(24);
	set_gfx_mode( GFX_AUTODETECT, xs, ys, 0, 0); // wybieramy rozdzielczoÅ›Ä‡ xs na ys

	usleep(10000);

	BITMAP * ekran_tytulowy = load_tga("ekran_tytulowy.tga", default_palette);

	blit(ekran_tytulowy, screen, 0, 0, 0, 0, xs, ys);
	
	while (!key[KEY_SPACE]) {
		usleep(20000);
	}

	clear_to_color(screen, makecol(0,0,0));

	// rysujemy powierzchnię księżyca
	
	int wierzcholki[22] = { 0, 700, 200, 750, 300, 680, 440, 720, 600, 700, 900, 733, 1021, 722, 1321, 740, 1366, 700, 1366,768, 0, 768 };

	polygon(screen, 11, wierzcholki, makecol(100,100,100));
	
	// rysujemy lądowisko

	rectfill(screen, 623, 700, 743, 720, makecol(100,0,0));
	
	// pozycja naszego ladowiska (lewy dolny róg)
	
	double x = rand() % (xs/2) + (xs/4);
	double y = 60;

	// wektor prędkości
	
	double dx = (rand() % 100 - 50)/30;
	double dy = 0;
		
	// paliwo
	
	double paliwo = 30;
	
	while (!key[KEY_ESC]) {
		// zmazujemy statek i odrzut po bokach
		
		rectfill(screen, x-10,y,x+25,y-40, makecol(0,0,0));
		
		// wypisujemy prędkość statku i ilość paliwa
		
		rectfill(screen, 0,0,xs,10, makecol(0,0,100));
		
		int v_kolor;

		if (sqrt(dx*dx + dy*dy) > 3) {
			v_kolor = makecol(255,0,0);
		} else {
			v_kolor = makecol(255,255,255);
		}
			
		textprintf_right_ex(screen, font, xs/2 - 100, 0, v_kolor, makecol(0,0,100), "V = %f", sqrt(dx*dx + dy*dy));
		
		textprintf_ex(screen, font, xs/2 + 100, 0, makecol(255,255,255), makecol(0,0,100), "Paliwo = %f", paliwo);
		
		// obliczamy nową pozycję
		
		x = x + dx;
		y = y + dy;
		
		// wykrywamy kolizje
		
		for (int i = 0; i <= 15; i++) {
			if (getpixel(screen, x+i,y) != makecol(0,0,0)) {

				if (getpixel(screen,x+i,y) == makecol(100,0,0) && (sqrt(dx*dx + dy*dy) <= 3)) {
					// rysujemy statek
			
					rectfill(screen, x, y, x + 15, y - 40, makecol(0,0,40));

					// ladowisko i wystarczająco mała prędkość
					
					for (int i = 0; i < xs; i++) {
						if (key[KEY_ESC]) { break; }
						
						rectfill(screen,i,0,i,768,makecol(0,0,20));
						
						textprintf_centre_ex(screen, font, xs/2, ys/2-20, makecol(255,255,255), makecol(0,0,0), "YOU WON!");
						textprintf_centre_ex(screen, font, xs/2, ys/2+20, makecol(255,255,255), makecol(0,0,0), "SCORE: %d", (int) (paliwo * 1000));
						usleep(5000);
					}
					
					cout << "Win! Score: " << (int) (paliwo*1000) << endl;
					
					return 0;
				} 

				// rysujemy statek
			
				rectfill(screen, x, y, x + 15, y - 40, makecol(0,0,40));

				// eksplozja
								
				for (int i = 1; i < 100; i++) {
					if (key[KEY_ESC]) { break; }
					
					circlefill(screen, x+8,y, i, makecol(255-2*i,255-2*i,0));
					textprintf_centre_ex(screen, font, xs/2, ys/2, makecol(255,255,255), makecol(0,0,0), "GAME OVER");
					usleep(40000);
				}
				
				cout << "You failed. Try again!" << endl;
				
				return 0;
			}
		}


		 
		// rysujemy statek
			
		rectfill(screen, x, y, x + 15, y - 40, makecol(0,0,40));

		// odrzut
		
		if (key[KEY_LEFT] && paliwo >= 0.1) {
			dx = dx - 0.05;

			paliwo -= 0.1;
			
			rectfill(screen, x+16,y-28,x+19,y-32, makecol(255,255,0));
		} else {
			rectfill(screen, x+16,y-28,x+19,y-32, makecol(0,0,0));
		}
		
		if (key[KEY_RIGHT] && paliwo >= 0.1) {
			dx = dx + 0.05;
			
			paliwo -= 0.1;
			
			rectfill(screen, x-1,y-28,x-4,y-32,makecol(255,255,0));
		} else {
			rectfill(screen, x-1,y-28,x-4,y-32,makecol(0,0,0));
		}
		
		if (key[KEY_UP] && paliwo >= 0.3) {
			dy = dy - 0.12;
			
			paliwo -= 0.3;
			
			rectfill(screen, x,y,x+15,y-3,makecol(200+rand()%56,200+rand()%56,0)); 
		}
		
		// grawitacja
		
		dy = dy + 0.05;
		
		
		usleep(20000);
	}
	
	return 0;
}
END_OF_MAIN();
