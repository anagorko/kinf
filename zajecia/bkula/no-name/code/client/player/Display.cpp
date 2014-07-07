#include "Display.h"

#include <string>

Display* Display::this_copy = NULL;

Area screen() { return *(Display::this_copy->area); }
int mouse_x() { return Display::this_copy->mouse_x; }
int mouse_y() { return Display::this_copy->mouse_y; }
bool mouse_pressed() { return Display::this_copy->mouse_pressed; }
void backToDisplay() { al_get_display_event_source(Display::this_copy->display); }

Display::Display() throw(Error) : closed(false), mouse_pressed(false), FPS(30)
{
    this_copy = this;

    if (!al_init()) {
        throw Error(__FILE__, __LINE__, "Błąd podczas inicjalizacji allegro.");
    }

    if (!al_init_primitives_addon()) {
        throw Error(__FILE__, __LINE__, "Błąd podczas inicjalizacji prymitywów.");
    }

    if (!al_init_image_addon()) {
        throw Error(__FILE__, __LINE__, "Błąd podczas inicjalizacji obrazów.");
    }

    al_init_font_addon();

    if (!al_init_ttf_addon()) {
        throw Error(__FILE__, __LINE__, "Błąd podczas inicjalizacji ttf.");
    }

    if (!al_install_keyboard()) {
        throw Error(__FILE__, __LINE__, "Błąd podczas inicjalizacji klawiatury.");
    }

    if (!al_install_mouse()) {
        throw Error(__FILE__, __LINE__, "Błąd podczas inicjalizacji myszy.");
    }

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_get_display_mode(0, &display_mode);

    area = new Area(Area::XYWH, 0, 0, display_mode.width, display_mode.height);

    display = al_create_display(screen().w(), screen().h());
    if(!display) {
        throw Error(__FILE__, __LINE__, "Błąd podczas inicjalizacji ekranu.");
    }
    al_set_window_title (display,
    []()->const char* {
        stringstream ss;
        ss << "Ustaw nazwę okna (" << __FILE__ << ":" << to_string(__LINE__) << ")";
        return ss.str().c_str();
    }() );

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        throw Error(__FILE__, __LINE__, "Błąd podczas inicjalizacji zegara.");
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        throw Error(__FILE__, __LINE__, "Błąd podczas inicjalizacji kolejki zdarzeń.");
    }

    for (int i = 0; i < ALLEGRO_KEY_MAX; ++i) {
        key[i] = false;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    al_start_timer(timer);
}

Display::~Display()
{
    this_copy = NULL;
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}

bool key(int n) throw(Error)
{
    try {
        if (n < 0 || n >= ALLEGRO_KEY_MAX) {
            throw Error(__FILE__, __LINE__, "Pytanie o nieistniejący klawisz");
        }
    } catch (const Error& e) {
        return false;
    }

    return Display::this_copy->key[n];
}

void Display::eventLoop(void(*update)(), void(*draw)(), void(*whenWindowClosed)())
{
    bool redraw = true;

    while (!closed) {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {

            // minęła (1/FPS) część sekundy

            redraw = true;

            update();

        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            key[ev.keyboard.keycode] = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            key[ev.keyboard.keycode] = false;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            whenWindowClosed();
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
            ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            mouse_x = ev.mouse.x;
            mouse_y = ev.mouse.y;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mouse_pressed = false;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mouse_pressed = true;
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            draw();

            al_flip_display();
        }
    }
}
