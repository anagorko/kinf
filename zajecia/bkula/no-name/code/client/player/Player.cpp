#include "Player.h"

Player* Player::this_copy = NULL;

void setGameColor(const Color& color) { Player::this_copy->gameColor = color; }
Color getGameColor() { return Player::this_copy->gameColor; }

Player::Player() : gameColor(0,127,0), status(WAITING)
{
    this_copy = this;

    try {
        display = new Display();
    } catch (const Error& e) {
        cout << "Nie udało się utworzyć okna :(\n";
        delete display;
    }

    if (client != NULL) {
        stringstream ss;
        ss << "client = " << client;
        throw Error(__FILE__, __LINE__, ss.str());
    }

    menu = new GroupOfButtons(screen_w()/2, screen_h()/2, "Menu");
    menu->addButton("Utwórz grę", []{ this_copy->host.start(); this_copy->client = new WebsocketsClient("127.0.0.1"); });
    menu->addButton("Dołącz do gry", []{ this_copy->client = new WebsocketsClient("69.69.69.69"); });
    menu->addButton("Wyjdź", []{ closeGame(); });
}

Player::~Player()
{
    this_copy = NULL;

    host.stop();
    delete menu;
    delete client;
    delete display;
}

void Player::mainLoop()
{
    display->eventLoop(update, draw, whenWindowClosed);
}

void Player::update()
{
    if (key(ALLEGRO_KEY_ESCAPE)) closeGame(); //tymczasowo

    if (this_copy->client == NULL) {
        this_copy->menu->update();
    } else if (this_copy->status == WAITING) {
        //waiting_room.update();
    } else {
        //
    }
}

void Player::draw()
{
    al_clear_to_color(Color(255,255,255));

    if (this_copy->client == NULL) {
        this_copy->menu->draw();
    } else if (this_copy->status == WAITING) {
        //waiting_room.draw();
    } else {
        //
    }
}

void Player::whenWindowClosed()
{
    // tymczasowo
    closeGame();
}
