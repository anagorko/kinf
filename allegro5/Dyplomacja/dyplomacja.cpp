//
// Gra w Allegro 5. (C) Kółko Informatyczne Szkoły Żagle
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
using namespace std;
int main(){



    const int screen_w = 1400;   // szerokość ekranu (screen width)
    const int screen_h = 879;   // wysokość ekranu (screen height)
    
    void rysuj_plansze(){
    al_clear_to_color(al_map_rgb(0,0,0));  }

    int t[76][6];
    int a; //zmienna kraju
    cout<<"Witaj w Dyplomacji 1914 na komputer. Jest to pierwsza wersja. Prosimy zgłaszaj swoje zastrzeżenia do gry na sdyplomacjanapc@gmail.com. Zapraszamy!\n";
    cout<<"Wybierz swoj kraj.\n";
    cout<<"1 Anglia, 2 Francja, 3 Niemcy, 4 Austro-Węgry, 5 Włochy, 6 Rosja, 7 Turcja\n";
    cin>> a;
    



   for(int i=19;i<62;i++){
       t[i][3]=0;
}
   if(a==1){
t[19][3]=1;
t[20][3]=1;
t[21][3]=1;
t[22][3]=1;
t[23][3]=1;
t[24][3]=1; }
    if(a==2){
t[25][3]=2;
t[26][3]=2;
t[27][3]=2;
t[28][3]=2;
t[29][3]=2;
t[30][3]=2;  }        
    if(a==3){
t[31][3]=3;
t[32][3]=3;
t[33][3]=3;
t[34][3]=3;
t[35][3]=3;
t[36][3]=3;  }
    if(a==4){
t[37][3]=4;
t[38][3]=4;
t[39][3]=4;
t[40][3]=4;
t[41][3]=4;
t[42][3]=4;  }
    if(a==5){
t[43][3]=5;
t[44][3]=5;
t[45][3]=5;
t[46][3]=5;
t[47][3]=5;
t[48][3]=5;  }
    if(a==6){
t[49][3]=6;
t[50][3]=6;
t[51][3]=6;
t[52][3]=6;
t[53][3]=6;
t[54][3]=6;
t[55][3]=6;  }
    if(a==7){
t[56][3]=7;
t[57][3]=7;
t[58][3]=7;
t[59][3]=7;
t[60][3]=7;
t[61][3]=7;  }



for(int i=0;i<19;i++){    
    t[i][0]=0;
}
for(int i=19;i<24;i++){
    t[i][0]=1;
}
for(int i=24;i<30;i++){
    t[i][0]=2;
}
for(int i=30;i<36;i++){
    t[i][0]=3;
}
for(int i=36;i<42;i++){
    t[i][0]=4;
}
for(int i=42;i<48;i++){
    t[i][0]=5;
}
for(int i=48;i<55;i++){
    t[i][0]=6;
}
for(int i=55;i<61;i++){
    t[i][0]=7;
}
for(int i=62;i<75;i++){
    t[i][0]=0;
}




for(int i=0;i<76;i++){    
    t[i][1]=0;
}
for(int i=19;i<25;i++){
    t[i][1]=1;
}
for(int i=25;i<31;i++){
    t[i][1]=2;
}
for(int i=32;i<37;i++){
    t[i][1]=3;
}
for(int i=37;i<43;i++){
    t[i][1]=4;
}
for(int i=43;i<49;i++){
    t[i][1]=5;
}
for(int i=49;i<56;i++){
    t[i][1]=6;
}
for(int i=56;i<62;i++){
    t[i][1]=7;
}



for(int i=0;i<76;i++){    
    t[i][2]=0;
}
for(int i=19;i<22;i++){    
    t[i][2]=1;
}
for(int i=25;i<28;i++){   // 43 45 49 52
    t[i][2]=2;
}
for(int i=31;i<34;i++){
    t[i][2]=3;
}
for(int i=37;i<40;i++){
    t[i][2]=4;
}
for(int i=43;i<46;i++){
    t[i][2]=5;
}
for(int i=49;i<53;i++){
    t[i][2]=6;
}
for(int i=56;i<59;i++){
    t[i][2]=7;
}





t[0][2]=0;    //jednostki
t[1][2]=0;
t[2][2]=0;
t[3][2]=0;
t[4][2]=0;
t[5][2]=0;
t[6][2]=0;
t[7][2]=0;
t[8][2]=0;
t[9][2]=0;
t[10][2]=0;
t[11][2]=0;
t[12][2]=0;
t[13][2]=0;
t[14][2]=0;
t[15][2]=0;
t[16][2]=0;
t[17][2]=0;
t[18][2]=0;

t[19][2]=1;
t[20][2]=1;
t[21][2]=1;

t[22][2]=0;
t[23][2]=0;
t[24][2]=0;

t[25][2]=2;
t[26][2]=2;
t[27][2]=2;

t[28][2]=0;
t[29][2]=0;
t[30][2]=0;

t[31][2]=3;
t[32][2]=3;
t[33][2]=3;

t[34][2]=0;
t[35][2]=0;
t[36][2]=0;

t[37][2]=4;
t[38][2]=4;
t[39][2]=4;

t[40][2]=0;
t[41][2]=0;
t[42][2]=0;

t[43][2]=5;
t[44][2]=5;
t[45][2]=5;

t[46][2]=0;
t[47][2]=0;
t[48][2]=0;

t[49][2]=6;
t[50][2]=6;
t[51][2]=6;
t[52][2]=6;

t[53][2]=0;
t[54][2]=0;
t[55][2]=0;

t[56][2]=7;
t[57][2]=7;
t[58][2]=7;

t[59][2]=0;
t[60][2]=0;
t[61][2]=0;
t[62][2]=0;
t[63][2]=0;
t[64][2]=0;
t[65][2]=0;
t[66][2]=0;
t[67][2]=0;
t[68][2]=0;
t[69][2]=0;
t[70][2]=0;
t[71][2]=0;
t[72][2]=0;
t[73][2]=0;
t[74][2]=0;
t[75][2]=0;

t[0][3]=0;    //wybór
t[1][3]=0;
t[2][3]=0;
t[3][3]=0;
t[4][3]=0;
t[5][3]=0;
t[6][3]=0;
t[7][3]=0;
t[8][3]=0;
t[9][3]=0;
t[10][3]=0;
t[11][3]=0;
t[12][3]=0;
t[13][3]=0;
t[14][3]=0;
t[15][3]=0;
t[16][3]=0;
t[17][3]=0;
t[18][3]=0;
t[62][3]=0;
t[63][3]=0;
t[64][3]=0;
t[65][3]=0;
t[66][3]=0;
t[67][3]=0;
t[68][3]=0;
t[69][3]=0;
t[70][3]=0;
t[71][3]=0;
t[72][3]=0;
t[73][3]=0;
t[74][3]=0;
t[75][3]=0;





              
BITMAP * buffer = create_bitmap(1400, 879);              

ALLEGRO_BITMAP *  = NULL;             
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
BITMAP * europa = NULL;
                                                                     //if (key[KEY_SPACE])
                                                                    //       printf("Space is pressed\n");

void aktualizuj_plansze()
{














}
void co_robia_gracze()
{







}
int init()
{
    if(!al_init()) {
        cerr << "Błąd podczas inicjalizacji allegro." << endl;
        return -1;
    }
  
    if (!al_init_primitives_addon()) {
        cerr << "Błąd podczas inicjalizacji dodatku 'primitives'." << endl;
        return -1;
    }
    
    if (!al_install_keyboard()) {
        cerr << "Błąd podczas inicjalizacji klawiatury." << endl;
        return -1;
    }

    if (!al_install_mouse()) {
        cerr << "Błąd podczas inicjalizacji myszy." << endl;
        return -1;
    }
  
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        cerr << "Błąd podczas inicjalizacji zegara." << endl;
        return -1;
    }
 
    display = al_create_display(screen_w, screen_h);
    if(!display) {
        cerr << "Błąd podczas inicjalizacji ekranu." << endl;
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        cerr << "Błąd podczas inicjalizacji kolejki zdarzeń." << endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
  
    al_register_event_source(event_queue, al_get_display_event_source(display));  
    al_register_event_source(event_queue, al_get_timer_event_source(timer));  
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));
  
    al_flip_display();  
    al_start_timer(timer);

    return 0;
}

int main(int argc, char ** argv)
{
    if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }
 
    bool przerysuj = true;
    bool wyjdz = false;  
 while(!wyjdz)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            //
            // minęła 1/60 (1/FPS) część sekundy
            //
            przerysuj = true;

            co_robia_gracze();

            aktualizuj_plansze();

        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            key[ev.keyboard.keycode] = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            key[ev.keyboard.keycode] = false;
            
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                wyjdz = true;
            }
        }

        if(przerysuj && al_is_event_queue_empty(event_queue)) {
            przerysuj = false;

            rysuj_plansze();

            al_flip_display();
         }    
    }

    return 0;

allegro_exit();


}














