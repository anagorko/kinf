#include<allegro.h>
#include<cstdlib>
int main(){
    allegro_init();
    install_keyboard();
    set_color_depth( 32 );
   set_gfx_mode( GFX_AUTODETECT_WINDOWED , 1366, 768, 0, 0 );//może być GFX_AUTODETECT(bez: _WINDOWED); 
    clear_to_color( screen, makecol( 0, 0, 0 ) );
	BITMAP* over = NULL;
	BITMAP* Pause = NULL;
	over = load_bmp("game_over.bmp",default_palette);
	Pause = load_bmp("Pause.bmp" , default_palette);
	int t[10000][2],ta[10000][2];
	long long int pocz=10,pocza=pocz;
	long long int kon=0,kona=kon;
	int a=rand()%10,b=rand()%10;
	char kier= 'N',kiera= 'G';
	bool czy=true;
	int dead=0;
	int nitro0=12,nitro1=24,nitro=12, nitrob1=nitro1+12,nitrob2=nitro1+24,nitrob3=nitro1+36,nitrob4=nitro1+48;
	install_mouse();
 int takiejzmiennejjeszczeniebylo=0;
	int kolo= makecol(42, 79, 171);
    show_mouse( screen );
   unscare_mouse();


	for (int i = 0; i < pocz+1; i++) {
		t[i][0] = 120; t[i][1] = 300 + i * 12;
		ta[i][0]= 240; ta[i][1]= 300 + i * 12;
	}
dead=0;
while(!key[KEY_ESC]){
if(key[KEY_UP] && kier != 'S'){ kier = 'N';}
if(key[KEY_RIGHT] && kier != 'W'){ kier = 'E';}
if(key[KEY_LEFT] && kier != 'E'){ kier = 'W';}
if(key[KEY_DOWN] && kier != 'N'){ kier = 'S';}

if(key[KEY_W] && kiera != 'D'){ kiera = 'G';}
if(key[KEY_D] && kiera != 'L'){ kiera = 'P';}
if(key[KEY_A] && kiera != 'P'){ kiera = 'L';}
if(key[KEY_S] && kiera != 'G'){ kiera = 'D';}




pocza++; kona++;
pocz++; kon++;
t[pocz][0] = t[pocz-1][0];
t[pocz][1] = t[pocz-1][1];

ta[pocza][0] = ta[pocza-1][0];
ta[pocza][1] = ta[pocza-1][1];


if (kier == 'N'){
	if(nitro==24){//............................................
	int nitrew=12;//					//
		for(int ghjk=kon;ghjk<=pocz;ghjk++){		//
		t[ghjk][1] -=nitrew;				//Przyspieszenie
		nitrew += 12;					//Czemu nie dziala!!!
		}						//
	}else{							//
	t[pocz][1] -=nitro;					//
	}//							//
}//.................................................................
if(kier == 'S'){
t[pocz][1] +=nitro;}
if(kier == 'W'){
t[pocz][0] -=nitro;}
if(kier == 'E'){
t[pocz][0] +=nitro;}




if (kiera == 'G') {
        ta[pocza][1] -=12;}
if(kiera == 'D'){
        ta[pocza][1] +=12;}
if(kiera == 'L'){
        ta[pocza][0] -=12;}
if(kiera == 'P'){
        ta[pocza][0] +=12;}
//.................................................................................................
				if(dead>=10){								//
					for(int s=0;s<100;s++){						//
					blit(over, screen, 0 , 0 , 0 , 0 , over->w, over->h);}		//DEAD
					allegro_exit();							//
					 return 0;}							//
//.................................................................................................

if(key[KEY_RCONTROL]){nitro=nitro1;}		//<--------------Czemu nie wchodzi ctrol!!!
if(!key[KEY_RCONTROL]){nitro=nitro0;}		//<--------------VIM

	if(takiejzmiennejjeszczeniebylo>=1){takiejzmiennejjeszczeniebylo++;}
	if(takiejzmiennejjeszczeniebylo>=4){takiejzmiennejjeszczeniebylo=0;kolo=makecol(57, 212, 104);}

	clear_to_color(screen,makecol(0,0,0));
	for (long long int i = kon; i < pocz; i++) {
	 if(t[pocz][0]<=-1){t[pocz][0]=1344;}
	 if(t[pocz][0]>1344){t[pocz][0]=0;}
	 if(t[pocz][1]>720){t[pocz][1]=0;}
 	 if(t[pocz][1]<=-1){t[pocz][1]=720;}

		if(nitro==12){rectfill(screen, t[i][0], t[i][1], t[i][0] + 10, t[i][1] + 10, kolo);}
		if(nitro==24){rectfill(screen, t[i][0], t[i][1], t[i][0] + 10, t[i][1] + 10, kolo);}
}
	 for (long long int i = kona; i < pocza; i++) {
	   if(ta[pocza][0]<=-1){ta[pocza][0]=1344;}
	   if(ta[pocza][0]>1344){ta[pocza][0]=0;}
	   if(ta[pocza][1]>720){ta[pocza][1]=0;}
	   if(ta[pocza][1]<=-1){ta[pocza][1]=720;}


                rectfill(screen, ta[i][0], ta[i][1], ta[i][0] + 10, ta[i][1] + 10, makecol(42, 79, 171)); }
//.........................................................................................
	if(key[KEY_SPACE]){									//
		while(key[KEY_SPACE]){blit(Pause, screen, 0, 0, 0, 0, Pause->w, Pause->h);}	//
		while(!key[KEY_SPACE]){blit(Pause, screen, 0, 0, 0, 0, Pause->w, Pause->h);	//Pause
			if(key[KEY_ESC]){allegro_exit();return 0;}}				//
	        while(key[KEY_SPACE]){blit(Pause, screen, 0, 0, 0, 0, Pause->w, Pause->h);}}	//
//...........................................................................................
	if(key[KEY_ALT] && key[KEY_F4]){					//
		while(key[KEY_ALT] && key[KEY_F4]){}				//
			if(!key[KEY_ALT] && !key[KEY_F4]){			//Czemu TO nie dziala!!!
			allegro_exit();return 0;				//
			}							//
	}									//
//..................................................................................
		for(int y=kon;y<=pocz;y++){
			for(int r=kon;r<=pocz;r++){
				if(ta[r][0]==t[y][0] && ta[r][1]==t[y][1]){kolo=makecol(255,0,0);takiejzmiennejjeszczeniebylo=1;dead++;}
			}
		}
//......................................................................................................
			if(kon==1000){									//
			kon=0;kona=0;									//
			pocz=10;pocza=10;								//
				for(int as=0;as<=10;as++){						//powracanie na poczatek petli
				t[as][0]=t[100-as][0];							//
				t[as][1]=t[100-as][1];							//
			}	}									//
//......................................................................................................
	if(key[KEY_ALT]){
		while(key[KEY_ALT]){
			if(key[KEY_F4] && key[KEY_ALT]){allegro_exit();return 0;}
		}
	}
		if(key[KEY_ALT] && key[KEY_F4]){allegro_exit();return 0;}


   usleep(30000);

}for(int i=0;i<100;i++){
blit(over, screen, 0 , 0 , 0 , 0 , over->w, over->h);
}
	allegro_exit();
    return 0;
}
END_OF_MAIN();
