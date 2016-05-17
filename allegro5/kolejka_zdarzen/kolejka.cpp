#include <iostream>
using namespace std;

#include <allegro5/allegro.h>

int main(int, char**)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    if (!al_init() || !al_install_mouse() || !al_install_keyboard()) {
        cout << "Inicjalizacja nie powiodła się." << endl; return -1;
    }
    
    timer = al_create_timer(1.0);
    display = al_create_display(800, 600);
    event_queue = al_create_event_queue();
    
    if (!timer || !display || !event_queue) {
        cout << "Inicjalizacja nie powiodła się." << endl; return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); 
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    while (true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        // https://www.allegro.cc/manual/5/ALLEGRO_EVENT
        
        cout << "Event type: " << ev.type << " - ";
        
        switch (ev.type) {
        case ALLEGRO_EVENT_KEY_DOWN: cout << "ALLEGRO_EVENT_KEY_DOWN"; 
            cout << " kod klawisza " << ev.keyboard.keycode;
            break;
        case ALLEGRO_EVENT_KEY_UP: cout << "ALLEGRO_EVENT_KEY_UP"; break;
        case ALLEGRO_EVENT_KEY_CHAR: cout << "ALLEGRO_EVENT_KEY_CHAR"; break;
        case ALLEGRO_EVENT_MOUSE_AXES: cout << "ALLEGRO_EVENT_MOUSE_AXES"; break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: cout << "ALLEGRO_EVENT_MOUSE_BUTTON_DOWN"; 
            cout << " współrzędne " << ev.mouse.x << " " << ev.mouse.y;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP: cout << "ALLEGRO_EVENT_MOUSE_BUTTON_UP"; break;
        case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY: cout << "ALLEGRO_EVENT_MOUSE_ENTER"; break;
        case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY: cout << "ALLEGRO_EVENT_MOUSE_LEAVE"; break;
        case ALLEGRO_EVENT_TIMER: cout << "ALLEGRO_EVENT_TIMER"; break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE: cout << "ALLEGRO_EVENT_DISPLAY_CLOSE"; break;
        }
        
        cout << endl;
    }
        
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

    return 0;
}
