//
// (C) Marcin Szcząchor
//

#include<allegro.h>
#include<iostream>
#include<math.h>

using namespace std;

const int xs = 1000, ys = 500;

int main()
{
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	set_gfx_mode( GFX_AUTODETECT, xs, ys, 0, 0);

	if (!screen) {
		cout << "Nie udalo sie otworzyc okna." << endl;
		return 1;
	}

	BITMAP * car = load_bitmap("car.tga", default_palette);
	BITMAP * car2 = load_bitmap("car1.tga", default_palette);
	BITMAP * buf = create_bitmap(xs, ys);
	float a = 0;
	float s = 0;
	float a2 = 0;
	float s2 = 0;
	float d=1, d2=1;
	float sk, sk2,f=1,f2=1,l=0;
	int stan=0;
	float x = xs/2, y = ys/2;
	float x2 = xs/3, y2 = ys/3;

	while(!key[KEY_ENTER]) {

		//clear_to_color(screen, makecol(0,0,0));
		blit(buf,screen,0,0,0,0,xs,ys);
		clear_to_color(buf, makecol(0,0,0));
		if (stan == 0)
		{
			textprintf_centre_ex(buf, font, xs/2, ys/2-20, makecol(255,0,0), makecol(0,0,0), "Start");
		}
		else
		{
			textprintf_centre_ex(buf, font, xs/2, ys/2-20, makecol(255,255,255), makecol(0,0,0), "Start");
		}

		if (stan == 1)
		{
			textprintf_centre_ex(buf, font, xs/2, ys/2-10, makecol(255,0,0), makecol(0,0,0), "Exit");
		}
		else
		{
			textprintf_centre_ex(buf, font, xs/2, ys/2-10, makecol(255,255,255), makecol(0,0,0), "Exit");
		}

		if (key[KEY_UP])stan--;
		if (key[KEY_DOWN])stan++;
		stan=stan%2;
		if (stan<0)stan += 2;

		usleep(100000);
		
	}
		
	if (stan == 0)
	{
	
	while (!key[KEY_ESC]) {
		clear_to_color(buf, makecol(0,0,0));
		rotate_sprite(buf, car, x, y, ftofix(a * 256.0 / 360.0));
		rotate_sprite(buf, car2, x2, y2, ftofix(a2 * 256.0 / 360.0));
		if(x<0 || y<0 || x>xs || y>ys)
		{
			s=s-s-s;
		}

		if(x2<0 || y2<0 || x2>xs || y2>ys)
		{
			s2=s2-s2-s2;
		}

		if (key[KEY_LEFT]) {
			a = a - 2;
		}
		if (key[KEY_RIGHT]) {
			a = a + 2;
		}
		if (key[KEY_UP]) {
			s = s + 0.4;
		}
		if (key[KEY_DOWN]) {
			if (s > -3) {
				s = s - 0.4;
			}
		}

		if (key[KEY_A]) {
			a2 = a2 - 2;
		}
		if (key[KEY_D]) {
			a2 = a2 + 2;
		}
		if (key[KEY_W]) {
			s2 = s2 + 0.4;
		}
		if (key[KEY_S]) {
			if (s2 > -3) {
				s2 = s2 - 0.4;
			}
		}

		if (key[KEY_M]) {
		a = 0;
		s = 0;
		y = ys/2;
		x = xs/2;
		}

		if (key[KEY_R]) {
		a2 = 0;
		s2 = 0;
		y2 = ys/3;
		x2 = xs/3;
		}

		if (key[KEY_N])
		{
			if(f==1){
			if (d==1) d=0;
			else d=1;
			f--;
			}
		}

		if (key[KEY_Z])
		{
			if(f2==1){
			if (d2==1) d2=0;
			else d2=1;
			f2--;
			}
		}

		if(d==1)sk=a;
		if(d2==1)sk2=a2;

		l++;

		if(l>=10){
		l=0;
		f=1;
		f2=1;
		}

		if (s!=0)
        {
		x = x + s * cos(sk / 360.0 * 2 * 3.14159);
		y = y + s * sin(sk / 360.0 * 2 * 3.14159);
        }

        if(s2!=0)
        {
		x2 = x2 + s2 * cos(sk2 / 360.0 * 2 * 3.14159);
		y2 = y2 + s2 * sin(sk2 / 360.0 * 2 * 3.14159);
        }

		blit(buf, screen, 0, 0, 0, 0, xs, ys);
		usleep(50000);
	}
	}
}
END_OF_MAIN();

