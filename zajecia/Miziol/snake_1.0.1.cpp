#include<iostream>
#include<allegro.h>
using namespace std;
int main()
{

int kolor1=rand()%256;
int kolor2=rand()%256;
int kolor3=rand()%256;

allegro_init();
install_keyboard();
set_color_depth( 32 );
set_gfx_mode( GFX_AUTODETECT,1366, 768, 0, 0 );

int dl = 20;
int k[1000000][2];
int pocz = 0;
int kon = dl - 1;

for (int i = 0; i < dl; i++) {
	k[i][0] = 683;
	k[i][1] = 384 - i;
}

while (!key[KEY_ESC]) {
	clear_to_color( screen, makecol( kolor1, kolor2, kolor3 ) );
	kon++;
		k[kon][0]=k[kon-1][0];
		k[kon][1]=k[kon-1][1];		

	if(kon==1000)
		{
		kon=0;
		}

	pocz++;
	
	if(pocz==1000)
		{
		pocz==0;
		}
	
	
	if(key[KEY_UP])
		{
		k[kon][1]=k[kon][1] - 6;		
		}
		
	if(key[KEY_DOWN])
		{
		k[kon][1]=k[kon][1] + 6;
		}

	if(key[KEY_LEFT])
		{
		k[kon][0]=k[kon][0] - 6;
		}

	if(key[KEY_RIGHT])
		{
		k[kon][0]=k[kon][0] + 6;
		}

	for (int i = 0; i < dl; i++) {
		circlefill( screen, k[pocz+i][0], k[pocz+i][1], 4, makecol(rand()%256,rand()%256,rand()%256) );
	}
	usleep(50000);
}	
}
