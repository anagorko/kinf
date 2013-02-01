/*************************************************************************
 * Sokoban - (C) Copyright 2012 Kółko Informatyczne Żagle                *
 *************************************************************************/

#include<allegro.h>
#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;

/*
 * Konfiguracja
 */

// rozdzielczość ekranu: 1024x768 - maksymalna rozdzielczość naszego rzutnika

const int screen_width = 1024;
const int screen_height = 768;
const int xs = 1024;
const int ys = 768;
int nr=0;
int plansza=0;
int poziom;


// wielkość kafli

const int tx = 35;
const int ty = 35;

// tło

const string background_image = "background.tga";

//
// Ładowanie poziomów "minicosmos" ze strony
// http://sneezingtiger.com/sokoban/levels.html
// Na tej stronie jest więcej poziomów - można dostosować
// program, by także je ściągał
//

// rozmiar tablicy z poziomami
const int max_levels = 100;

// rzeczywista liczba poziomów
int levels = 0;

// maksymalna wysokość poziomu
const int level_height = 20;

// pojedynczy poziom - tablica tablic napisów :)
typedef string level[level_height][2];

// tablica poziomów
level map[max_levels];

level original_map[max_levels];

level poprz_map[max_levels];

// kopiowanie poziomu z jednego miejsca do drugiego
void copy_level(level& l1, level& l2) {
	for (int i = 0; i < level_height; i++) {
		l2[i][0] = l1[i][0];
		l2[i][1] = l1[i][1];
	}
}

// UWAGA: ciekawe :)
// wypełnianie podłogi
void flood_fill(level& l, int x, int y) {
	if (y < 0 || y >= level_height) return;

	if (x < 0 || x >= (int) l[y][0].length()) return;

       
	if (l[y][1][x] == '#') return;

	if (l[y][0][x] == ' ') {
		l[y][0][x] = '-';
	} else if (l[y][0][x] == '=') {
		l[y][0][x] = '_';
	} else {
		return;
	}

	flood_fill(l, x-1,y);
	flood_fill(l, x+1,y);
	flood_fill(l, x,y-1);
	flood_fill(l, x,y+1);
}

// parser poziomów

void load_minicosmos_levels()
{
	string filename = "minicosmos.lvl";

	ifstream infile;

	infile.open(filename.c_str(), ifstream::in);

	while (!infile.eof()) {

		string w;
		infile >> w;

		if (w != "Level") {
			cout << "Invalid format (" << filename << ")" << endl;
			return;
		}
		
		int n;
		infile >> n;
		string lvl_name;
		
		infile.ignore();

		getline(infile, lvl_name);
		
		level lv;
		int li = 0;

		int px, py;

		do {
			string l;

			getline(infile, l);
			
			if (l == "") break;

			// rozdzielamy podloge od przedmiotow

			string l_g = l; // ground
			string l_o = l; // over ground

			for (unsigned int i = 0; i < l_g.length(); i++) {
				char t = l_g[i];

				switch (l_g[i]) {
				case '@': t = ' '; px = i; py = li; break;
				case '$': t = ' '; break;
				case '.': t = '='; break;
				case '#': t = ' '; break;
				case '*': t = '='; break;
				}

				l_g[i] = t;
			}

			for (unsigned int i = 0; i < l_o.length(); i++) {
				char t = l_o[i];
			       
				switch (l_o[i]) {
				case '@': t = 'v'; break;
				case '$': t = 'o'; break;
				case '.': t = ' '; break;
				case '*': t = 'o'; break;
				}

				l_o[i] = t;
			}

			lv[li][0] = l_g;
			lv[li][1] = l_o;

			li++;

		} while (li < level_height);

		for ( ; li < level_height; li++) {
			lv[li][0] = "******************************";
			lv[li][1] = "                              ";
		}

		flood_fill(lv, px, py);

		copy_level(lv, map[levels++]);

		for (int i = 0; i < level_height; i++) {
			cout << map[levels-1][i][0] << ", " << map[levels-1][i][1] << endl;
		}

		cout << "Loading level # " << n << ", " << lvl_name << endl;
	}	
}

// nasze mapy poziomów
// ZADANIE 9 - dodatkowe poziomy

level map1 =
	{
		// Pierwsza plansza. Autor: http://www.games4brains.de/sokoban-leveldesign.htm
		{ "******************************", "########                      " },
		{ "*--*---***********************", "e  #   #                      " },
		{ "*------***********************", "e   o  #                      " },
		{ "*--**-************************", "e o## #####                   " },
		{ "**-*_-**--********************", "#7 #  ##  #                   " },
		{ "**-*_-----********************", " e #    o #                   " },
		{ "**-*_-**--********************", " e #  ##  #                   " },
		{ "**-*_***-*********************", " e # ##e ##                   " },
		{ "**----**--********************", " ev   ##  #                   " },
		{ "***-------********************", " #7 o     #                   " },
		{ "********--********************", "  #nnnn#  #                   " },
		{ "******************************", "       #nn#                   " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " }
	};

level map2 = 
	{
		// Druga plansza. Autor:
		{ "******************************", "                              " },
		{ "******************************", "        ####                  " },
		{ "*********--*******************", "        #  #                  " },
		{ "*********--*******************", "    #####  ###                " },
		{ "*****---_----*****************", "    # o  o   #                " },
		{ "*****---__-_-*****************", "    # voo  o #                " },
		{ "*****-___--*******************", "    # o o  ###                " },
		{ "*******--*********************", "    ###  ###                  " },
		{ "*******--*********************", "      #  #                    " },
		{ "******************************", "      ####                    " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " },
		{ "******************************", "                              " }
	};

// wstawianie do tablicy naszych poziomów
void load_our_levels()
{
	copy_level(map1, map[levels++]);
	copy_level(map2, map[levels++]);
}

// Grafika

string tile_name[256];

// nazwy plików z grafiką
// ZADANIE 10 - Ulepszenie grafiki
void set_tile_names() {
	tile_name['*'] = "tiles/empty.tga";
	tile_name['-'] = "tiles/wall.tga";
	tile_name[' '] = "tiles/empty.tga";
	tile_name['_'] = "tiles/target.tga";

	tile_name['v'] = "tiles/player_S.tga";
	tile_name['^'] = "tiles/player_N.tga";
	tile_name['l'] = "tiles/player_W.tga";
	tile_name['r'] = "tiles/player_E.tga";

	tile_name['o'] = "tiles/box.tga";
	tile_name['#'] = "tiles/pavement.tga";
	tile_name['n'] = "tiles/wall_N.tga";
	tile_name['7'] = "tiles/wall_270_NE.tga";
	tile_name['e'] = "tiles/wall_E.tga";

	tile_name['z'] = "tiles/zła_babcia.tga";
}

BITMAP* tile[256];
BITMAP* bg;

// sprawdzenie, czy w mapie nie ma znaków bez przypisanego pliku graficznego
char validate_line(int level, int line)
{
	for (int j = 0; j < 2; j++) {
		for (unsigned int i = 0; i < map[level][line][j].length(); i++) {
			if (tile[(unsigned int) map[level][line][j][i]] == NULL) 
				return map[level][line][j][i];
		}
	}
	return 0;
}

// załadowanie kafli
void load_tiles() 
{	
	for (int a = 0; a <= 255; a++) {
		// nie każdy znak to bitmapa
		if (tile_name[a] != "") {
			cout << "Loading " << tile_name[a] << endl;

			tile[a] = load_tga(tile_name[a].c_str(), NULL);

			if (tile[a] == NULL) {
				// nie udało się załadować pliku - protestujemy!
				// (inaczej potem będzie "segmentation fault")
				cout << "Nie udało się otworzyć pliku " << tile_name[a] << "!\n";

				exit(1);
			}
		}
	}

	// skanujemy plansze poszukując symboli bez przypisanej grafiki

	for (int l = 0; l < levels; l++) {
		for (int i = 0; i < 20; i++) {
			char c = validate_line(l, i);
			if (c != 0) {
				cout << "Na mapie znajduje się znak '" << c << "' bez przypisanego pliku graficznego." << endl;

				exit(1);
			}
		}
	}

	// Tło ekranu
	bg = load_tga(background_image.c_str(), NULL);

	if (bg == NULL) {
		cout << "Nie mogę załadować pliku " << background_image << endl;
		exit(1);
	}
}

/*
 * Ludzik
 */

int steps = 0, pushes = 0;
int energy = 100;

// odszukanie ludzika na planszy
bool locate_player(int lvl, int &px, int &py) 
{
	for (int y = 0; y < 20; y++) {
		for (unsigned int x = 0; x < map[lvl][y][1].length(); x++) {
			if (map[lvl][y][1][x] == '^' ||
			    map[lvl][y][1][x] == 'v' ||
			    map[lvl][y][1][x] == 'l' ||
			    map[lvl][y][1][x] == 'r') {
				px = x;
				py = y;
				return true;
			}
		}
	}
	return false;
}

bool locate_stworek(int lvl, int &px, int &py)
{
	for (int y = 0; y < 20; y++) {
		for (unsigned int x = 0; x < map[lvl][y][1].length(); x++) {
			if (map[lvl][y][1][x] == 'z') {
				px = x;
				py = y;
				return true;
			}
		}
	}
	return false;
}

// czy wspołrzędne to punkt na mapie?
bool on_map(int lvl, int x, int y)
{
	if ((x < 0) || (y < 0) || (y >= 20) || ((unsigned int) x >= map[lvl][y][1].length())) {
		return false;
	}
	return true;
}

void save_level(int lvl)
{
	copy_level(map[lvl], poprz_map[lvl]);
}

// przesunięcie ludzika w kierunku (dx, dy)
void move_player(int lvl, int dx, int dy, char player_tile)
{
	int x,y;

	locate_player(lvl, x, y);

	if (on_map(lvl,x+dx, y+dy)) {
		if (map[lvl][y+dy][1][x+dx] == ' ' && energy >= 3) {
			save_level(lvl);

			map[lvl][y+dy][1][x+dx] = player_tile;
			map[lvl][y][1][x] = ' ';

			steps++;
			energy = 0;
		} else if (map[lvl][y+dy][1][x+dx] == 'o') {
			if (on_map(lvl,x+2*dx, y+2*dy)) {
				if (map[lvl][y+2*dy][1][x+2*dx] == ' ') {
					if (energy >= 6) {
						save_level(lvl);

						map[lvl][y+2*dy][1][x+2*dx] = 'o';
						map[lvl][y+dy][1][x+dx] = player_tile;
						map[lvl][y][1][x] = ' ';

						energy = 0;
						pushes++;
					}
				}
			}
		}
	}
}



// liczenie wyniku
void count_score(int lvl, int &done, int &total) 
{
	total = 0;
	done = 0;

	for (int y = 0; y < level_height; y++) {
		for (unsigned int x = 0; x < map[lvl][y][0].length(); x++) {
			if (map[lvl][y][0][x] == '_') {
				total++;
				if (map[lvl][y][1][x] == 'o') {
					done++;
				}
			}
		}
	}
}

/***********************************************************************
 * Rysowanie planszy
 ***********************************************************************/

const int lx = 400;
const int ly = 300; // (lx, ly) - współrzędne lewego górnego rogu planszy na ekranie

void draw_level(BITMAP* buffer, int lvl) {
	// rysujemy całą planszę
	for (int y = 0; y < 20; y++) {
		for (unsigned int x = 0; x < map[lvl][y][0].length(); x++) {
			masked_blit(tile[(unsigned int) map[lvl][y][0][x]], buffer, 0, 0, lx + x*tx, ly + y*ty, tx, ty);
		}
		for (unsigned int x = 0; x < map[lvl][y][1].length(); x++) {
			masked_blit(tile[(unsigned int) map[lvl][y][1][x]], buffer, 0, 0, lx + x*tx, ly + y*ty, tx, ty);
		}
	}
}

void wczytaj_poziom()
{
	int n=325, m=5, bok=1;
	bool byl_puszczony = true;
	bool byl_puszczony2 = true;
	bool byl_puszczony3 = true;
	bool byl_puszczony4 = true;

	BITMAP * bufo = create_bitmap(screen_width, screen_height);

	BITMAP * ll1 = load_tga("Levels High/1.tga", default_palette);	
	BITMAP * ll2 = load_tga("Levels Low/2.tga", default_palette);
	BITMAP * ll3 = load_tga("Levels Low/3.tga", default_palette);
	BITMAP * ll4 = load_tga("Levels Low/4.tga", default_palette);
	BITMAP * ll5 = load_tga("Levels Low/5.tga", default_palette);
	BITMAP * ll6 = load_tga("Levels Low/6.tga", default_palette);
	BITMAP * ll7 = load_tga("Levels Low/7.tga", default_palette);

	BITMAP * ll8 = load_tga("Levels Low/8.tga", default_palette);
	BITMAP * ll9 = load_tga("Levels Low/9.tga", default_palette);
	BITMAP * ll10 = load_tga("Levels Low/10.tga", default_palette);
	BITMAP * ll11 = load_tga("Levels Low/11.tga", default_palette);
	BITMAP * ll12 = load_tga("Levels Low/12.tga", default_palette);
	BITMAP * ll13 = load_tga("Levels Low/13.tga", default_palette);
	BITMAP * ll14 = load_tga("Levels Low/14.tga", default_palette);	

	BITMAP * ll15 = load_tga("Levels Low/15.tga", default_palette);
	BITMAP * ll16 = load_tga("Levels Low/16.tga", default_palette);
	BITMAP * ll17 = load_tga("Levels Low/17.tga", default_palette);
	BITMAP * ll18 = load_tga("Levels Low/18.tga", default_palette);
	BITMAP * ll19 = load_tga("Levels Low/19.tga", default_palette);
	BITMAP * ll20 = load_tga("Levels Low/20.tga", default_palette);
	BITMAP * ll21 = load_tga("Levels Low/21.tga", default_palette);	

	BITMAP * ll22 = load_tga("Levels Low/22.tga", default_palette);
	BITMAP * ll23 = load_tga("Levels Low/23.tga", default_palette);
	BITMAP * ll24 = load_tga("Levels Low/24.tga", default_palette);
	BITMAP * ll25 = load_tga("Levels Low/25.tga", default_palette);
	BITMAP * ll26 = load_tga("Levels Low/26.tga", default_palette);
	BITMAP * ll27 = load_tga("Levels Low/27.tga", default_palette);
	BITMAP * ll28 = load_tga("Levels Low/28.tga", default_palette);

	BITMAP * ll29 = load_tga("Levels Low/29.tga", default_palette);
	BITMAP * ll30 = load_tga("Levels Low/30.tga", default_palette);
	BITMAP * ll31 = load_tga("Levels Low/31.tga", default_palette);
	BITMAP * ll32 = load_tga("Levels Low/32.tga", default_palette);
	BITMAP * ll33 = load_tga("Levels Low/33.tga", default_palette);
	BITMAP * ll34 = load_tga("Levels Low/34.tga", default_palette);
	BITMAP * ll35 = load_tga("Levels Low/35.tga", default_palette);

	BITMAP * ll36 = load_tga("Levels Low/36.tga", default_palette);
	BITMAP * ll37 = load_tga("Levels Low/37.tga", default_palette);
	BITMAP * ll38 = load_tga("Levels Low/38.tga", default_palette);
	BITMAP * ll39 = load_tga("Levels Low/39.tga", default_palette);
	BITMAP * ll40 = load_tga("Levels Low/40.tga", default_palette);
	BITMAP * ll41 = load_tga("Levels Low/41.tga", default_palette);
	BITMAP * ll42 = load_tga("Levels Low/42.tga", default_palette);
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	BITMAP * lh2 = load_tga("Levels High/2.tga", default_palette);
	BITMAP * lh3 = load_tga("Levels High/3.tga", default_palette);
	BITMAP * lh4 = load_tga("Levels High/4.tga", default_palette);
	BITMAP * lh5 = load_tga("Levels High/5.tga", default_palette);
	BITMAP * lh6 = load_tga("Levels High/6.tga", default_palette);
	BITMAP * lh7 = load_tga("Levels High/7.tga", default_palette);

	BITMAP * lh8 = load_tga("Levels High/8.tga", default_palette);
	BITMAP * lh9 = load_tga("Levels High/9.tga", default_palette);
	BITMAP * lh10 = load_tga("Levels High/10.tga", default_palette);
	BITMAP * lh11 = load_tga("Levels High/11.tga", default_palette);
	BITMAP * lh12 = load_tga("Levels High/12.tga", default_palette);
	BITMAP * lh13 = load_tga("Levels High/13.tga", default_palette);
	BITMAP * lh14 = load_tga("Levels High/14.tga", default_palette);	

	BITMAP * lh15 = load_tga("Levels High/15.tga", default_palette);
	BITMAP * lh16 = load_tga("Levels High/16.tga", default_palette);
	BITMAP * lh17 = load_tga("Levels High/17.tga", default_palette);
	BITMAP * lh18 = load_tga("Levels High/18.tga", default_palette);
	BITMAP * lh19 = load_tga("Levels High/19.tga", default_palette);
	BITMAP * lh20 = load_tga("Levels High/20.tga", default_palette);
	BITMAP * lh21 = load_tga("Levels High/21.tga", default_palette);	

	BITMAP * lh22 = load_tga("Levels High/22.tga", default_palette);
	BITMAP * lh23 = load_tga("Levels High/23.tga", default_palette);
	BITMAP * lh24 = load_tga("Levels High/24.tga", default_palette);
	BITMAP * lh25 = load_tga("Levels High/25.tga", default_palette);
	BITMAP * lh26 = load_tga("Levels High/26.tga", default_palette);
	BITMAP * lh27 = load_tga("Levels High/27.tga", default_palette);
	BITMAP * lh28 = load_tga("Levels High/28.tga", default_palette);

	BITMAP * lh29 = load_tga("Levels High/29.tga", default_palette);
	BITMAP * lh30 = load_tga("Levels High/30.tga", default_palette);
	BITMAP * lh31 = load_tga("Levels High/31.tga", default_palette);
	BITMAP * lh32 = load_tga("Levels High/32.tga", default_palette);
	BITMAP * lh33 = load_tga("Levels High/33.tga", default_palette);
	BITMAP * lh34 = load_tga("Levels High/34.tga", default_palette);
	BITMAP * lh35 = load_tga("Levels High/35.tga", default_palette);

	BITMAP * lh36 = load_tga("Levels High/36.tga", default_palette);
	BITMAP * lh37 = load_tga("Levels High/37.tga", default_palette);
	BITMAP * lh38 = load_tga("Levels High/38.tga", default_palette);
	BITMAP * lh39 = load_tga("Levels High/39.tga", default_palette);
	BITMAP * lh40 = load_tga("Levels High/40.tga", default_palette);
	BITMAP * lh41 = load_tga("Levels High/41.tga", default_palette);
	BITMAP * lh42 = load_tga("Levels High/42.tga", default_palette);

	BITMAP * menu = load_tga("menu3.tga", default_palette);
	blit(menu, screen, 0, 0, 0, 0, screen_width, screen_height);
	
while(!key[KEY_ESC])
{
	blit(bufo,screen,0,0,0,0,screen_width, screen_height);		
	blit(menu, bufo, 0, 0, 0, 0, screen_width, screen_height);

	blit(ll1,bufo,0,0,325,300,50,50);

	if(poziom>=1) blit(lh2,bufo,0,0,325,360,50,50);
	else blit(ll2,bufo,0,0,325,360,50,50);

	if(poziom>=1)blit(lh3,bufo,0,0,325,420,50,50);
	else blit(ll3,bufo,0,0,325,420,50,50); 

	if(poziom>=3) blit(lh4,bufo,0,0,325,480,50,50);
	else blit(ll4,bufo,0,0,325,480,50,50);

	if(poziom>=4) blit(lh5,bufo,0,0,325,540,50,50);
	else blit(ll5,bufo,0,0,325,540,50,50);

	if(poziom>=5) blit(lh6,bufo,0,0,325,600,50,50);
	else blit(ll6,bufo,0,0,325,600,50,50);

	if(poziom>=6) blit(lh7,bufo,0,0,325,660,50,50);
	else blit(ll7,bufo,0,0,325,660,50,50);


	if(poziom>=7) blit(lh8,bufo,0,0,385,300,50,50);
	else blit(ll8,bufo,0,0,385,300,50,50);

	if(poziom>=8) blit(lh9,bufo,0,0,385,360,50,50);
	else blit(ll9,bufo,0,0,385,360,50,50);

	if(poziom>=9) blit(lh10,bufo,0,0,385,420,50,50);
	else blit(ll10,bufo,0,0,385,420,50,50);

	if(poziom>=10) blit(lh11,bufo,0,0,385,480,50,50);
	else blit(ll11,bufo,0,0,385,480,50,50);

	if(poziom>=11) blit(lh12,bufo,0,0,385,540,50,50);
	else blit(ll12,bufo,0,0,385,540,50,50);

	if(poziom>=12) blit(lh13,bufo,0,0,385,600,50,50);
	else blit(ll13,bufo,0,0,385,600,50,50);

	if(poziom>=13) blit(lh14,bufo,0,0,385,660,50,50);
	else blit(ll14,bufo,0,0,385,660,50,50);

	if(poziom>=14) blit(lh15,bufo,0,0,445,300,50,50);
	else blit(ll15,bufo,0,0,445,300,50,50);

	if(poziom>=15) blit(lh16,bufo,0,0,445,360,50,50);
	else blit(ll16,bufo,0,0,445,360,50,50);

	if(poziom>=16) blit(lh17,bufo,0,0,445,420,50,50);
	else blit(ll17,bufo,0,0,445,420,50,50);

	if(poziom>=17) blit(lh18,bufo,0,0,445,480,50,50);
	else blit(ll18,bufo,0,0,445,480,50,50);

	if(poziom>=18) blit(lh19,bufo,0,0,445,540,50,50);
	else blit(ll19,bufo,0,0,445,540,50,50);

	if(poziom>=19) blit(lh20,bufo,0,0,445,600,50,50);
	else blit(ll20,bufo,0,0,445,600,50,50);

	if(poziom>=20) blit(lh21,bufo,0,0,445,660,50,50);
	else blit(ll21,bufo,0,0,445,660,50,50);

	
	if(poziom>=21) blit(lh22,bufo,0,0,505,300,50,50);
	else blit(ll22,bufo,0,0,505,300,50,50);

	if(poziom>=22) blit(lh23,bufo,0,0,505,360,50,50);
	else blit(ll23,bufo,0,0,505,360,50,50);

	if(poziom>=23) blit(lh24,bufo,0,0,505,420,50,50);
	else blit(ll24,bufo,0,0,505,420,50,50);

	if(poziom>=24) blit(lh25,bufo,0,0,505,480,50,50);
	else blit(ll25,bufo,0,0,505,480,50,50);

	if(poziom>=25) blit(lh26,bufo,0,0,505,540,50,50);
	else blit(ll26,bufo,0,0,505,540,50,50);

	if(poziom>=26) blit(lh27,bufo,0,0,505,600,50,50);
	else blit(ll27,bufo,0,0,505,600,50,50);

	if(poziom>=27) blit(lh28,bufo,0,0,505,660,50,50);
	else blit(ll28,bufo,0,0,505,660,50,50);


	if(poziom>=28) blit(lh29,bufo,0,0,565,300,50,50);
	else blit(ll29,bufo,0,0,565,300,50,50);

	if(poziom>=19) blit(lh30,bufo,0,0,565,360,50,50);
	else blit(ll30,bufo,0,0,565,360,50,50);

	if(poziom>=30) blit(lh31,bufo,0,0,565,420,50,50);
	else blit(ll31,bufo,0,0,565,420,50,50);

	if(poziom>=31) blit(lh32,bufo,0,0,565,480,50,50);
	else blit(ll32,bufo,0,0,565,480,50,50);

	if(poziom>=32) blit(lh33,bufo,0,0,565,540,50,50);
	else blit(ll33,bufo,0,0,565,540,50,50);

	if(poziom>=33) blit(lh34,bufo,0,0,565,600,50,50);
	else blit(ll34,bufo,0,0,565,600,50,50);

	if(poziom>=34) blit(lh35,bufo,0,0,565,660,50,50);
	else blit(ll35,bufo,0,0,565,660,50,50);


	if(poziom>=35) blit(lh36,bufo,0,0,625,300,50,50);
	else blit(ll36,bufo,0,0,625,300,50,50);

	if(poziom>=36) blit(lh37,bufo,0,0,625,360,50,50);
	else blit(ll37,bufo,0,0,625,360,50,50);

	if(poziom>=37) blit(lh38,bufo,0,0,625,420,50,50);
	else blit(ll38,bufo,0,0,625,420,50,50);

	if(poziom>=38) blit(lh39,bufo,0,0,625,480,50,50);
	else blit(ll39,bufo,0,0,625,480,50,50);

	if(poziom>=39) blit(lh40,bufo,0,0,625,540,50,50);
	else blit(ll40,bufo,0,0,625,540,50,50);

	if(poziom>=40) blit(lh41,bufo,0,0,625,600,50,50);
	else blit(ll41,bufo,0,0,625,600,50,50);

	if(poziom>=41) blit(lh42,bufo,0,0,625,660,50,50);
	else blit(ll42,bufo,0,0,625,660,50,50);

	rect(bufo, n, 60*m, n+50, 60*m+50, makecol( 155,1,1 ) );
	rect(bufo, n-1, 60*m-1, n+1+50, 60*m+1+50, makecol( 155,1,1 ) );

	if(key[KEY_DOWN] && byl_puszczony) {
		m++;
		if(m==12 && bok==6){
			m=5;
			bok=1;
		}
		if(m==12) {
			m=5;
			bok++;
		}
		if(bok==1) n=325;
		else if(bok==2) n=385;
		else if(bok==3) n=445;
		else if(bok==4) n=505;
		else if(bok==5) n=565;
		else if(bok==6) n=625;
		if(bok==7) {
			bok=1;
		}
		byl_puszczony=false;
	}
	if (!key[KEY_DOWN]) { byl_puszczony = true; }

	if(key[KEY_UP] && byl_puszczony2) {
		m--;
		if(m==4 && bok==1){
			m=11;
			bok=6;
		}
		if(m==4) {
			m=11;
			bok--;
		}
		if(bok==1) n=325;
		else if(bok==2) n=385;
		else if(bok==3) n=445;
		else if(bok==4) n=505;
		else if(bok==5) n=565;
		else if(bok==6) n=625;
		if(bok==0) {
			bok=6;
		}		

		byl_puszczony2=false;
	}
	if (!key[KEY_UP]) { byl_puszczony2 = true; }

	if(key[KEY_RIGHT] && byl_puszczony3) {
	    bok++;
		if(bok==1) n=325;
		else if(bok==2) n=385;
		else if(bok==3) n=445;
		else if(bok==4) n=505;
		else if(bok==5) n=565;
		else if(bok==6) n=625;
		if(bok==7) {
			bok=1;
			n=325;
			m++;
		}
		if(bok==1) n=325;
		else if(bok==2) n=385;
		else if(bok==3) n=445;
		else if(bok==4) n=505;
		else if(bok==5) n=565;
		else if(bok==6) n=625;
		if(bok==0) {
			bok=6;
			n=625;
		}
		if(m==12) m=5;
		byl_puszczony3=false;
	}
	if (!key[KEY_RIGHT]) { byl_puszczony3 = true; }

	if(key[KEY_LEFT] && byl_puszczony4) {
		bok--;
		if(bok==1) n=325;
		else if(bok==2) n=385;
		else if(bok==3) n=445;
		else if(bok==4) n=505;
		else if(bok==5) n=565;
		else if(bok==6) n=625;
		if(bok==0) {
			bok=6;
			n=625;
			m--;
		}
		if(m==4) m=11;
		byl_puszczony4=false;
	}
	if (!key[KEY_LEFT]) { byl_puszczony4 = true; }

	if(key[KEY_ESC]) nr=0;

}//while levels		

}//void levels

void inst()
{
	BITMAP * bufo = create_bitmap(screen_width, screen_height);

	BITMAP * menu = load_tga("menu3.tga", default_palette);
	blit(menu, screen, 0, 0, 0, 0, screen_width, screen_height);

	BITMAP * instrukcja = load_tga("przyciski/instrukcja.tga", default_palette);	
	
	while (!key[KEY_ESC]) {

		blit(bufo,screen,0,0,0,0,screen_width, screen_height);		
		blit(menu, bufo, 0, 0, 0, 0, screen_width, screen_height);
		blit(instrukcja,bufo,0,0,350,300,300,300);
	
		if(key[KEY_ESC]) nr=0;
	}
}

void menus()
{//menus
		
	BITMAP * buf = create_bitmap(screen_width, screen_height);

	BITMAP * menu = load_tga("menu3.tga", default_palette);
	blit(menu, screen, 0, 0, 0, 0, screen_width, screen_height);

	BITMAP * start_low = load_tga("przyciski/nowa_gra4.tga", default_palette);
	BITMAP * start_high = load_tga("przyciski/nowa_gra3.tga", default_palette);

	BITMAP * zakoncz_low = load_tga("przyciski/koniec4.tga", default_palette);
	BITMAP * zakoncz_high = load_tga("przyciski/koniec3.tga", default_palette);

	BITMAP * instrukcja_low = load_tga("przyciski/instrukcja_button.tga", default_palette);
	BITMAP * instrukcja_high = load_tga("przyciski/instrukcja_button2.tga", default_palette);

	BITMAP * wczytaj_low = load_tga("przyciski/wczytaj_poziom2.tga", default_palette);
	BITMAP * wczytaj_high = load_tga("przyciski/wczytaj_poziom.tga", default_palette);

	BITMAP * instrukcja = load_tga("przyciski/instrukcja.tga", default_palette);

	//MUZYKA
	SAMPLE * dzwiek = load_wav( "tiles/nom.wav" );

	bool byl_puszczony = true;
	bool byl_puszczony2 = true;

	while (!key[KEY_ENTER]) {
	
		blit(menu, buf, 0, 0, 0, 0, screen_width, screen_height);

		//MUZYKA
		play_sample( dzwiek, 255, 127, 1000, 1 );

		if (nr == 0 || nr == 2 || nr == 3 || nr == 4) {
			blit(start_low,buf,0,0,350,350,300,50);
		} else {
			blit(start_high,buf,0,0,350,350,300,50);
		}

		if (nr == 0 || nr == 1 || nr == 3 || nr == 4) {
			blit(wczytaj_low,buf,0,0,350,430,300,50);
		} else {
			blit(wczytaj_high,buf,0,0,350,430,300,50);
		}

		if (nr == 0 || nr == 1 || nr == 2 || nr == 4) {
			blit(instrukcja_low,buf,0,0,350,510,300,50);
		} else {
			blit(instrukcja_high,buf,0,0,350,510,300,50);
		}          	

		if (nr == 0 || nr == 1 || nr == 2 || nr == 3) {
			blit(zakoncz_low,buf,0,0,350,590,300,50);
		} else {
			blit(zakoncz_high,buf,0,0,350,590,300,50);
		}          
	
	if(key[KEY_DOWN] && byl_puszczony)
        {
            byl_puszczony = false;
            nr++;
            if(nr>4) nr=1;
        }

	if (!key[KEY_DOWN]) { byl_puszczony = true; }

        if(key[KEY_UP] && byl_puszczony2)
        {
	    byl_puszczony2 = false;           
            nr--;
            if(nr<1) nr=4;
        }

	if (!key[KEY_UP]) { byl_puszczony2 = true; }

	
	blit(buf,screen,0,0,0,0,screen_width, screen_height);
	usleep(10000);

	if(key[KEY_ENTER])
        {
        if(nr==1)
        {
            //main_loop();
			plansza=0;
			break;
        }
		if(nr==2)
		{
			wczytaj_poziom();
		}
		if(nr==3)
		{
			inst();
		}
		if(nr==0 || nr==4)
        {
           	//return 0;
       	}

	}

}//while enter
}//void menus


// główna pętla w grze

void main_loop()
{

       	// Bufor wykorzystywany w technice "double buffering"
	// Potrzebny po to, żeby gracz nie widział jak rysowany jest obraz
 	BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);

	// ta zmienna to numer pokazywanej planszy
	///////////////////////////////////////////////int plansza = 0;

	while (!key[KEY_ESC]) { 		
		energy++;

		// wyświetlamy zawartość bufora na ekranie;
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	       
		// rysujemy tło (zamazując wszystko)
		blit(bg, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);

		if (key[KEY_LEFT]) {
			move_player(plansza,-1,0,'l');

		}

		if (key[KEY_RIGHT]) {
			move_player(plansza,1,0,'r');

		}

		if (key[KEY_UP]) {
			move_player(plansza,0,-1,'^');

		}

		if (key[KEY_DOWN]) {
			move_player(plansza,0,1,'v');
			
		}

		// ZADANIE 1 - przeskakiwanie poziomu
	       
     		draw_level(buffer, plansza);

		// wynik

		int done, total;		
		count_score(plansza, done, total);

		textprintf_ex(buffer, font, 10, 10, makecol(255,255,255),-1, "Poziom %d. Wynik %d/%d. Kroki: %d. Pchnięcia: %d.", plansza + 1, done, total, steps, pushes);

		if (done == total) {
			// poziom ukończony - przechodzimy do następnej planszy

			// ZADANIE 2 - informacja o ukończeniu poziomu i krótka pauza
			plansza++;

			if (plansza >= levels) { plansza = 0; }
		}

		if(key[KEY_E])
		{
			plansza++;
			while(key[KEY_E]) {}
			
		}
		
		if(key[KEY_Q])
		{
			plansza--;
			while(key[KEY_Q]) {}
			if(plansza<0)
			{
				plansza=41;
			}
			
		}


		if(key[KEY_R])
		{
			for(int i=0; i<levels; i++)
			{
			copy_level(original_map[i], map[i]);
			}
			while(key[KEY_R]) {}
		}

		if(key[KEY_C])
		{
			for(int i=0; i<levels; i++)
			{
			copy_level(poprz_map[plansza], map[plansza]);
			}
			while(key[KEY_C]) {}
		}


		// czekamy 1/50 sekundy
		usleep(20000);
	}

	if(key[KEY_ESC])
	{//
		nr=0;
		poziom=plansza;
		menus();
	}//

}


int main()
{ 

		

	// Wywołujemy naszą funkcję ustawiającą nazwy plików z grafiką
	// w tablicy plik

	set_tile_names();

	load_minicosmos_levels();
	load_our_levels();

	// Standardowa inicjalizacja allegro
	allegro_init();
	install_keyboard();
	
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, "" );//instalacja dzwieku
	set_volume( 125, 125 );//ustawienia glosnosci

	// przejście do trybu graficznego
	set_color_depth(24);
	set_gfx_mode( GFX_AUTODETECT, screen_width, screen_height, 0, 0);

	// Ładowanie bitmap. 
	load_tiles();

	// ZADANIE 4 - plansza początkowa
	


	for (int i = 0; i < levels; i++) {
		copy_level(map[i], original_map[i]);


	}

	//menu
	menus();

	if(nr==0 || nr==4)
	{
		return 0;
	}

	// gramy
	main_loop();

	if(nr==0 || nr==4)
	{
		return 0;
	}
	else if(nr==3) inst();
	else if(nr==2) wczytaj_poziom();
	else if(nr==1) main_loop();

	// ZADANIE 5 - koniec gry

	return 0;
}
END_OF_MAIN();
