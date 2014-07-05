#include "Player.h"

Player* Player::this_copy = NULL;

void setGameColor(const Color& color) { Player::this_copy->gameColor = color; }
Color getGameColor() { return Player::this_copy->gameColor; }

Player::Player() : gameColor(0, 0, 127), status(WAITING), closing(false)
{
    this_copy = this;

    try {
        display = new Display();
    } catch (const Error& e) {
        cout << "Nie udało się utworzyć okna :(\n";
        delete display;
    }

    if (web_client != NULL) {
        stringstream ss;
        ss << "web_client = " << web_client;
        throw Error(__FILE__, __LINE__, ss.str());
    }

    closing_window = new GroupOfButtons(screen_w()/2, screen_h()/2, "Jesteś pewien, że chcesz perwać grę?", 24);
    closing_window->addButton("Opuść grę", []{ closeGame(); }, Color(200, 0, 0));
    closing_window->addButton("Anuluj", []{ this_copy->closing = false; }, Color(0, 200, 0));

    menu = new GroupOfButtons(screen_w()/2, screen_h()/2, "Menu", 32);
    menu->addButton("Utwórz grę", []{ this_copy->host.start(); this_copy->web_client = new WebsocketsClient("127.0.0.1"); });
    menu->addButton("Dołącz do gry", []{ this_copy->web_client = new WebsocketsClient("69.69.69.69"); });
    menu->addButton("Wyjdź", []{ closeGame(); });
}

Player::~Player()
{
    this_copy = NULL;

    host.stop();
    delete menu;
    delete web_client;
    delete display;
}

void Player::mainLoop()
{
    display->eventLoop(update, draw, whenWindowClosed);
}

void Player::update()
{
    if (key(ALLEGRO_KEY_ESCAPE)) {
        if (this_copy->web_client == NULL) closeGame();
        else this_copy->closing = true;
    }

    if (this_copy->closing) {
        this_copy->closing_window->update();

    } else if (this_copy->web_client == NULL) {
        this_copy->menu->update();

    } else if (this_copy->status == WAITING) {
        this_copy->waiting_room.update();

    } else {
        this_copy->game_room.update();
    }
}

void Player::draw()
{
    al_clear_to_color(Color(255,255,255));

    if (this_copy->web_client == NULL) {
        this_copy->menu->draw();

    } else if (this_copy->status == WAITING) {
        this_copy->waiting_room.draw();

    } else {
        this_copy->game_room.draw();
    }

    if (this_copy->closing) this_copy->closing_window->draw();
}

void Player::whenWindowClosed()
{
    // tymczasowo
    closeGame();
}
