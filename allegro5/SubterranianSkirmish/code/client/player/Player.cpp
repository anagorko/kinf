#include "Player.h"

Player* Player::this_copy = NULL;

void setGameColor(const Color& color) { Player::this_copy->gameColor = color; }
Color getGameColor() { return Player::this_copy->gameColor; }

bool receivePacket(Packet &payload) throw(Error)
{
    Packet::receivePacketTemplate(Player::this_copy->web_client, payload);
}

void sendCommand(Data::Commands command, string args) throw(Error)
{
    Packet::sendCommandTemplate(Player::this_copy->web_client, command, args);
}

const ClientData& getData() throw(Error)
{
    if (!Player::this_copy->data) {
        throw Error(__FILE__, __LINE__, "Próba pobrania nieistniejących danych");
    }

    return *(Player::this_copy->data);
}

Player::Player() : gameColor(0, 0, 127), status(WAITING), scene(MAIN_MENU), escWasPressed(false), connection_failed(NULL)
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

    waiting_room = new WaitingRoom([]{ this_copy->host.stop(); delete this_copy->web_client; this_copy->web_client = NULL; });

    leaving_the_game = new GroupOfButtons(screen().cx(), screen().cy(), "Jesteś pewien, że chcesz perwać grę?", Scale::bk(24));
    leaving_the_game->addButton("Opuść grę", []{ closeGame(); }, Color(200, 0, 0));
    leaving_the_game->addButton("Anuluj", []{ this_copy->scene = MAIN_MENU; }, Color(0, 200, 0));

    main_menu = new GroupOfButtons(screen().cx(), screen().cy(), "Menu", Scale::bk(32), Color(0, 127, 0));
    main_menu->addButton("Utwórz grę", []{ this_copy->scene = CREATING_THE_GAME; });
    main_menu->addButton("Dołącz do gry", []{ this_copy->scene = ATTACHING_TO_GAME; });
    main_menu->addButton("Wyjdź", []{ closeGame(); });

    attaching_to_game = new GroupOfButtons(screen().cx(), screen().cy(), "", Scale::bk(30), Color::purple());
    attaching_to_game->addTextbox(&server_adress, "Adres IP servera");
    attaching_to_game->addTextbox(&my_nick, "Twój nick");
    attaching_to_game->addButton("Dołącz do gry", []{ this_copy->tryConnectToServer(); });
    attaching_to_game->addButton("Anuluj", []{ this_copy->scene = MAIN_MENU; });

    creating_the_game = new GroupOfButtons(screen().cx(), screen().cy(), "Podaj swój nick", Scale::bk(30), Color::purple());
    creating_the_game->addTextbox(&my_nick);
    creating_the_game->addButton("Utwórz grę", []{ this_copy->tryConnectToServer(true); });
    creating_the_game->addButton("Anuluj", []{ this_copy->scene = MAIN_MENU; });
}

Player::~Player()
{
    this_copy = NULL;

    // usuwanie scen
    delete waiting_room;
    delete main_menu;
    delete leaving_the_game;
    delete attaching_to_game;
    delete creating_the_game;

    host.stop();
    delete web_client;
    delete display;
}

void Player::mainLoop()
{
    display->eventLoop(update, draw, whenWindowClosed);
}

void Player::update()
{
    setMouseCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    if (key(ALLEGRO_KEY_ESCAPE)) this_copy->escWasPressed = true;

    if (this_copy->scene == LEAVING_THE_GAME) {
        this_copy->leaving_the_game->update();

    } else if (this_copy->web_client == NULL) {

        switch (this_copy->scene) {
        case MAIN_MENU:
            if (this_copy->escWasPressed && !key(ALLEGRO_KEY_ESCAPE)) closeGame();
            this_copy->main_menu->update();
            break;
        case ATTACHING_TO_GAME:
            if (this_copy->escWasPressed && !key(ALLEGRO_KEY_ESCAPE)) this_copy->scene = MAIN_MENU;
            this_copy->attaching_to_game->update();
            break;
        case CREATING_THE_GAME:
            if (this_copy->escWasPressed && !key(ALLEGRO_KEY_ESCAPE)) this_copy->scene = MAIN_MENU;
            this_copy->creating_the_game->update();
            break;
        case CONNECTION_FAILED:
            if (this_copy->escWasPressed && !key(ALLEGRO_KEY_ESCAPE)) this_copy->scene = ATTACHING_TO_GAME;
            this_copy->connection_failed->update();
            break;
        default:
            throw Error(__FILE__, __LINE__, "Nierozpoznana scena");
        }

    } else if (this_copy->status == WAITING) {
        if (this_copy->escWasPressed && !key(ALLEGRO_KEY_ESCAPE)) WaitingRoom::whenClosed();
        this_copy->waiting_room->update();

    } else {
        if (this_copy->escWasPressed && !key(ALLEGRO_KEY_ESCAPE)) this_copy->scene = LEAVING_THE_GAME;
        this_copy->game_room.update();
    }

    if (!key(ALLEGRO_KEY_ESCAPE)) this_copy->escWasPressed = false;
}

void Player::draw()
{
    if (this_copy->web_client == NULL) {

        drawGradient(screen(), Color::white(), Color::yellow(), false);

        switch (this_copy->scene) {
        case MAIN_MENU:
            this_copy->main_menu->draw();
            break;
        case ATTACHING_TO_GAME:
            this_copy->attaching_to_game->draw();
            break;
        case CREATING_THE_GAME:
            this_copy->creating_the_game->draw();
            break;
        case CONNECTION_FAILED:
            this_copy->connection_failed->draw();
            break;
        default:
            throw Error(__FILE__, __LINE__, "Nierozpoznana scena");
        }

    } else if (this_copy->status == WAITING) {
        this_copy->waiting_room->draw();

    } else {
        this_copy->game_room.draw();
    }

    if (this_copy->scene == LEAVING_THE_GAME) {
        al_draw_filled_rectangle(0, 0, screen().w(), screen().h(), al_map_rgba(0,0,0,180));
        this_copy->leaving_the_game->draw();
    }
}

void Player::whenWindowClosed()
{
    // tymczasowo
    closeGame();
}

string getServer()
{
    return Player::this_copy->web_client == NULL ? "" : Player::this_copy->web_client->getServer();
}

void Player::tryConnectToServer(bool server_is_mine)
{
    delete web_client;

    try
    {
        web_client = new WebsocketsClient([=]{ return server_is_mine ? "127.0.0.1" : server_adress; }());
    }
    catch (Error& e)
    {
        host.stop();
        delete web_client;
        web_client = NULL;
        scene = CONNECTION_FAILED;
        delete connection_failed;
        connection_failed = new GroupOfButtons(screen().cx(), screen().cy(), e.statement, Scale::bk(28), Color::red()-30);
        if (server_is_mine) connection_failed->addButton("OK", []{ this_copy->scene = CREATING_THE_GAME; });
        else connection_failed->addButton("OK", []{ this_copy->scene = ATTACHING_TO_GAME; });

        return;
    }

    scene = MAIN_MENU;

    if (server_is_mine) host.start();

    // Wyślij paczkę o dołączeniu do gry z my_nickiem my_nick
}
