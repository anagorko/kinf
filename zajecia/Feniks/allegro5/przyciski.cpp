#include <iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int main(int, char**)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    if (!al_init() || !al_install_mouse() || !al_install_keyboard() ) {
        cout << "Inicjalizacja nie powiodła się." << endl; return -1;
    }

	al_init_primitives_addon();

    timer = al_create_timer(0.2);
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
	
	int mx,my;
	bool mp = false, blue = false;

    while (true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        // https://www.allegro.cc/manual/5/ALLEGRO_EVENT

        cout << "Event type: " << ev.type << " - ";

        switch (ev.type) {
        case ALLEGRO_EVENT_KEY_DOWN: cout << "ALLEGRO_EVENT_KEY_DOWN"; 
            cout << " kod klawisza " << ev.keyboard.keycode;
            break;

        case ALLEGRO_EVENT_KEY_UP: cout << "ALLEGRO_EVENT_KEY_UP";
		break;

        case ALLEGRO_EVENT_KEY_CHAR: cout << "ALLEGRO_EVENT_KEY_CHAR"; break;

        case ALLEGRO_EVENT_MOUSE_AXES: cout << "ALLEGRO_EVENT_MOUSE_AXES";
		mx=ev.mouse.x;
		my=ev.mouse.y;
		break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: cout << "ALLEGRO_EVENT_MOUSE_BUTTON_DOWN"; 
            cout << " współrzędne " << ev.mouse.x << " " << ev.mouse.y;
			mp = true;
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP: cout << "ALLEGRO_EVENT_MOUSE_BUTTON_UP";
		mp = false;
		break;

        case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY: cout << "ALLEGRO_EVENT_MOUSE_ENTER"; break;

        case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY: cout << "ALLEGRO_EVENT_MOUSE_LEAVE"; break;

        case ALLEGRO_EVENT_TIMER: cout << "ALLEGRO_EVENT_TIMER";
		if( mx < 320 && mx > 160 && my < 240 && my > 120 && mp == false)
		{
			al_draw_filled_rectangle( 160, 120, 320, 240, al_map_rgb( 0, 255, 0));
		}
		else if( mx < 320 && mx > 160 && my < 240 && my > 120 && mp == true)
		{
			al_draw_filled_rectangle( 160, 120, 320, 240, al_map_rgb( 0, 55, 0));
			blue = true;
		}
		else
		{
			al_draw_filled_rectangle( 160, 120, 320, 240, al_map_rgb( 0, 155, 0));
		}
		if( blue == true)
		{
			if( mx < 640 && mx > 480 && my < 480 && my > 360 && mp == false)
			{
				al_draw_filled_rectangle( 480, 360, 640, 480, al_map_rgb( 0, 0, 255));
			}
			else if( mx < 640 && mx > 480 && my < 480 && my > 360 && mp == true)
			{
				al_draw_filled_rectangle( 480, 360, 640, 480, al_map_rgb( 0, 0, 55));
			}
			else
			{
				al_draw_filled_rectangle( 480, 360, 640, 480, al_map_rgb( 0, 0, 155));
			}
		}

		al_flip_display();
		break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE: cout << "ALLEGRO_EVENT_DISPLAY_CLOSE"; break;
        }

        cout << endl;
    }

   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

    return 0;
}
