#include <allegro.h>
#include<iostream>
#include<math.h>

using namespace std;

const int xs = 1280, ys = 1024;//wymiary planszy

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

	int m=rand()%9+1;

	BITMAP * car = load_bitmap("tank1.tga", default_palette);//niebieski
	BITMAP * car2 = load_bitmap("tank2.tga", default_palette);//czerwony	
	
	BITMAP * buf = create_bitmap(xs, ys);//tło

	BITMAP * tlo = load_bitmap("m6.tga", default_palette);

	float kat = 180,kat2=0,p=0,p2=0;//kat-kąt skrętu; p-prędkość
	float x = xs/4, y = ys/2;//położenie t1
	float x2 = 3*(xs/4), y2 = ys/2;//położenie t2
	float pp=3,px=-1,py=-1,px2=-1,py2=-1,pkat=180,pkat2=0;
		
	while (!key[KEY_ESC]) {
		clear_to_color(buf, makecol(0,0,0));
		blit(tlo, buf, 0, 0, 0, 0, xs, ys);
		rotate_sprite(buf, car, x, y, ftofix(kat * 256.0 / 360.0));
		rotate_sprite(buf, car2, x2, y2, ftofix(kat2 * 256.0 / 360.0));
		circlefill(buf, px2, py2, 2, makecol(255,0,0));
		circlefill(buf, px, py, 2, makecol(0,0,255));

		if (key[KEY_4_PAD]||key[KEY_LEFT]) {
			if(p>0){kat = kat + 2;}
			else{kat = kat - 2;}
		}
		if (key[KEY_6_PAD]||key[KEY_RIGHT]) {
			if(p>0){kat = kat - 2;}
			else{kat = kat + 2;}
		}
		if (key[KEY_5_PAD]||key[KEY_DOWN]) {
			if(p==2){}
			if(p<=1.5){p=p+0.5;}
		}
		if (key[KEY_8_PAD]||key[KEY_UP]) {
			if(p==-2){}
			if(p>=-1.5){p=p-0.5;}
		}
		if (key[KEY_9_PAD]||key[KEY_M]) {
			px=x;
			py=y;
			if(kat<=180){pkat=kat+180;}
			else{pkat=kat-180;}
		}



		if (key[KEY_D]) {
			if(p2>0){kat2 = kat2 - 2;}
			else{kat2 = kat2 + 2;}
		}
		if (key[KEY_A]) {
			if(p2>0){kat2 = kat2 + 2;}
			else{kat2 = kat2 - 2;}
		}
		if (key[KEY_S]) {
			if(p2==2){}
			if(p2<=1.5){p2=p2+0.5;}
		}
		if (key[KEY_W]) {
			if(p2==-2){}
			if(p2>=-1.5){p2=p2-0.5;}
		}
		if (key[KEY_E]) {
			px2=x2;
			py2=y2;
			if(kat2<=180){pkat2=kat2+180;}
			else{pkat2=kat2-180;}
		}


		if (key[KEY_R]) {
		kat = 0;
		kat2=180;
		p=0;
		p2=0;
		x = 3*(xs/4);
		y = ys/2;
		x2 = xs/4;
		y2 = ys/2;
		pp=3;
		px=-1;
		py=-1;
		px2=-1;
		py2=-1;
		pkat=0;
		pkat2=180;	
		}

		px = px + pp * cos(pkat / 360.0 * 2 * 3.14159);
		py = py + pp * sin(pkat / 360.0 * 2 * 3.14159);

		px2 = px2 + pp * cos(pkat2 / 360.0 * 2 * 3.14159);
		py2 = py2 + pp * sin(pkat2 / 360.0 * 2 * 3.14159);

		x = x + p * cos(kat / 360.0 * 2 * 3.14159);
		y = y + p * sin(kat / 360.0 * 2 * 3.14159);

		x2 = x2 + p2 * cos(kat2 / 360.0 * 2 * 3.14159);
		y2 = y2 + p2 * sin(kat2 / 360.0 * 2 * 3.14159);

		blit(buf, screen, 0, 0, 0, 0, xs, ys);
		usleep(10000);
	}
}
END_OF_MAIN();

