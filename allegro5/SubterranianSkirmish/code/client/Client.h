#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <string>
using namespace std;

#include <allegro5/allegro_color.h>

#include "../Error.h"
#include "../WebsocketsClient.h"
#include "../Packet.h"
#include "ClientData.h"

/* Client to klasa bazowa dla Player i Bot
   definiuje system komunikacji klienta gry z hostem oraz jego kompetencje
   Client jest klasą wirtualną i tworzenie obiektów tego typu nie ma sensu */

class Client
{
public:

    Client() : web_client(NULL) {}
    virtual ~Client() {}
    virtual void mainLoop() = 0;

    friend const ClientData& getData() throw(Error);

protected:

    WebsocketsClient* web_client;

    const ClientData* data;
};

#endif // __CLIENT_H__
