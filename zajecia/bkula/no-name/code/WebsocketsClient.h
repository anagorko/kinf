#ifndef WEBSOCKETSCLIENT_H
#define WEBSOCKETSCLIENT_H

#include "Error.h"

// tymczasowy include:
#include "client/player/global.h"

class WebsocketsClient
{
public:

    WebsocketsClient(string _server) throw(Error);
    ~WebsocketsClient();

    // wysyła paczkę i automatycznie uruchamia serwis
    void sendPacket(string payload) throw(Error);

    // odbiera paczkę lub zwraca false jeżeli nie ma paczek do odebrania
    // przed użyciem należy uruchomić serwis
    bool receivePacket(string &payload);

    // serwis - aktualizuje listę paczek
    void serviceWebsockets() throw(Error);

    // zwraca adres serwera do z którym się połączyliśmy
    string getServer() const { return server; }

private:

    string server;
};

#endif // WEBSOCKETSCLIENT_H
