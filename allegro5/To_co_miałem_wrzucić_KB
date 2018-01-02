#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#define rozmiar_paczki 256

using namespace std;

//GLOBALLS
const int HEIGHT = 400;
const int WIDTH = 800;

enum KEYS{UP,DOWN,LEFT,RIGHT,SPACE};
enum GAMESTATE{MENU,SINGLE,OPTIONS,GAME,GAMEOVER};
bool keys[] = {false,false,false,false,false};
int game_state = GAME;


class Paczka
{
    public:
    int t[rozmiar_paczki];
};

struct Wykres
{
    vector<int> wartosci;
    void dodaj(int a)
    {
        wartosci.push_back(a);
    }
    void rysuj()
    {
        int ile = min(WIDTH,(int)wartosci.size());
        int i2=1;
        if((wartosci.size()) > WIDTH)
            i2=(wartosci.size() - WIDTH);
        for(int i=0; i<=ile;i++)
        {
            al_draw_line(i,HEIGHT,i,HEIGHT - wartosci[i2-1],al_map_rgb(255,i==0?0:255,i==0?0:255), 1);
            i2++;
        }
    }
};



int main()
{
    //variables
    bool done = false;
    bool redraw = true;
    const int FPS = 1;

    //object variables

    Wykres w;
    Paczka p;
    ///////////

    //ALLEGRO variables
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE  *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font8 = NULL;
    ALLEGRO_FONT *font18 = NULL;
    //Initiation Functions
    if(!al_init())
    {
        cout << "Initiation error!" << endl;
        return -1;
    }

    display = al_create_display(WIDTH,HEIGHT);

    if(!display)
    {
        cout << "Display error!" << endl;
        return -2;
    }

    al_init_font_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_ttf_addon();



    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);
    font8 = al_create_builtin_font();
    font18 = al_load_ttf_font("arial.ttf", 18, 0);

    srand(time(NULL));

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);
    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
             if(keys[UP])

            if(keys[DOWN])

            if(keys[LEFT])

            if(keys[RIGHT])


            if(game_state == GAME)
            {


            }
            else if(game_state == GAMEOVER)
            {

            }

        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_SPACE:

                keys[SPACE] = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;

            }


            /*if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;
            if(ev.keyboard.keycode == ALLEGRO_KEY_UP)
                keys[UP] = true;
            if(ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
                keys[DOWN] = true;
            if(ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
                keys[LEFT] = true;
            if(ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                keys[RIGHT] = true;
            if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
            {
                keys[SPACE] = true;
                FireBullet(bullets, NUM_BULLETS,p);
            }
            */
        }
       else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = false;
                break;
            }
        }


        //DRAWING 60 TIMES PER SEC
        if(redraw && al_is_event_queue_empty(event_queue))
        {

            redraw = false;
            if(game_state == GAME)
            {
                for(int i=0; i < rozmiar_paczki; i++)
                p.t[i] = rand()%400;


                for(int i=0; i<rozmiar_paczki; i++)
                    w.dodaj(p.t[i]);

                w.rysuj();
            }
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }
    al_destroy_font(font8);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);


    return 0;
}
