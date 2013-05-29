#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
using namespace std; //to modifikacja
int main(int argc, char** argv)
{
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    ALLEGRO_KEYBOARD_STATE klawiatura;
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY *okno = al_create_display(400,300);
    al_set_window_title( okno,"Allegro5 - Prymitywy");
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(okno));
    ALLEGRO_EVENT event;
        al_get_next_event(event_queue, &event);if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { return 0; }
        al_get_keyboard_state(&klawiatura);
        
        // istotna część kodu-tylko ona modifikowana
	char a;
	char b;
	cout<<"podaj co chcesz narysować\n"
	    <<"k=kwadrat\nt=trójkąt\no=koło\nl=linia\n";
	cin<<a;
	al_clear_to_color(al_map_rgb(255,255,255))
	switch(a);
	{
		case k:
		cout<<"czy wolisz wypełniony=w, czy niewypełniony=n\n";
		cin>>b;
		if (b=w)
		{
			 al_draw_filled_rectangle(280, 280,350, 350,al_map_rgb(,227,7,32));
		}
		else
		{
			 al_draw_rectangle(280,280,350, 350,al_map_rgb(227,7,32),4);	
		}	
		break;

		case t:
		cout<<"czy wolisz wypełniony=w, czy niewypełniony=n\n";
		cin>>b;
		if (b=w)
		{
			  al_draw_filled_triangle(280, 300, 220, 250, 300, 250, al_map_rgb(40,7,227));
		}
		else
		{
			al_draw_triangle(280, 300, 220, 250, 300, 250, al_map_rgb(40,7,227),4);	
		}	
		break;

		case o:
		cout<<"czy wolisz wypełnione=w, czy niewypełnione=n\n";
		cin>>b;
		if (b=w)
		{
			 al_draw_filled_circle(250,120, 34, al_map_rgb(233,245, 5));
		}
		else
		{
			 al_draw_circle(200,120, 30, al_map_rgb( 233,245, 5), 4);	
		}	
		break;

		case l:
		al_draw_line( 200, 150, 300, 100, al_map_rgb( 245, 105, 5, ), 4);
		break;

        al_flip_display();
        al_rest(10);

    usleep(10000000);
    al_destroy_display(okno);
    return 0;
}
