#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

struct punkt {
    int x;
    int y;
};

struct waz {
    struct punkt cielsko[10000];
    
    int dlugosc;
    
    struct punkt glowa;
};

struct waz w;

const int segment = 5;

int main(int argc, char ** argv){
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
 
    bool key[4] = { false, false, false, false };
    bool redraw = true;
    bool doexit = false;
  
    if(!al_init()) {
       fprintf(stderr, "failed to initialize allegro!\n");
       return -1;
    }
  
    if(!al_install_keyboard()) {
       fprintf(stderr, "failed to initialize the keyboard!\n");
       return -1;
    }
  
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
       fprintf(stderr, "failed to create timer!\n");
       return -1;
    }
 
    display = al_create_display(SCREEN_W, SCREEN_H);

     if(!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
     }

    al_set_target_bitmap(al_get_backbuffer(display));
  
    event_queue = al_create_event_queue();
    if(!event_queue) {
       fprintf(stderr, "failed to create event_queue!\n");
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
  
    w.glowa.x = 50;
    w.glowa.y = 50;
    
    w.dlugosc = 100;
    
    for (int i = 0; i < w.dlugosc; i++) {
        w.cielsko[i] = w.glowa;
    }
    
    while(!doexit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;

            if (key[KEY_UP]) {
                w.glowa.y = w.glowa.y - 1;
            }
            if (key[KEY_RIGHT]) {
                w.glowa.x = w.glowa.x + 1;
            }
            if (key[KEY_DOWN]) {
                w.glowa.y = w.glowa.y + 1;
            }
            if (key[KEY_LEFT]) {
                w.glowa.x = w.glowa.x - 1;
            }
            
            for (int i = 0; i < w.dlugosc - 1; i++) {
                w.cielsko[i] = w.cielsko[i+1];
            }
            
            w.cielsko[w.dlugosc - 1] = w.glowa;
            
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = true;
                break;
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = false;
                break;
            case ALLEGRO_KEY_ESCAPE:
                doexit = true;
                break;
            }
         }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0,0,0));
     
            for (int i = 0; i < w.dlugosc; i++) {
                al_draw_filled_rectangle(
                  w.cielsko[i].x * segment, 
                  w.cielsko[i].y * segment,
                  (w.cielsko[i].x+1) * segment - 1,
                  (w.cielsko[i].y+1) * segment - 1,
                  al_map_rgb(98,76,54));
            }
             
            al_flip_display();
         }    
    }

    return 0;
}
