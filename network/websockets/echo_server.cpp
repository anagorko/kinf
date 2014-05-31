#include<iostream>
#include<set>
using namespace std;

#include "websockets_server.h"

class EchoServer : public WebsocketsServer
{
    set<int> clients;
    
public:
    virtual void connectionEstablished(int id) {
        cout << "connectionEstablished(" << id << ")" << endl;
        
        clients.insert(id);
    }
    
    virtual void connectionClosed(int id) {
        cout << "connectionClosed(" << id << ")" << endl;
        clients.erase(id);
    }
    
    virtual void receivedData(int x, string packet) {
        cout << "receivedData(" << x << "," << packet << ")" << endl;
        for (int id: clients) {
            if (id != x) {
                send_packet(id, packet);
            }
        }
    }
};

int main(int arg, char** argv)
{
    EchoServer server;
    
    if (!server.start()) {
        cout << "Failed to initialize server. Server status: " << server.getStatus() << "." << endl;
        return 1;
    }
    
    server.enterLoop();

    cout << "Closing..." << endl;
        
    server.stop();
    
    return 0;
}
