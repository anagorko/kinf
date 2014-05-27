#ifndef __WEBSOCKETS_SERVER__
#define __WEBSOCKETS_SERVER__

#include<list>
#include<vector>
using namespace std;

#include "libwebsockets.h"

void sighandler(int sig);

class WebsocketsServer
{
public:
    static int _callback_kinf(struct libwebsocket_context *context,
		struct libwebsocket *wsi,
		enum libwebsocket_callback_reasons reason, void *user,
							   void *_in, size_t len);
							   
    static int _callback_http(struct libwebsocket_context *context,
		struct libwebsocket *wsi,
		enum libwebsocket_callback_reasons reason, void *user,
							   void *_in, size_t len);

    static bool force_exit;

private:
    int port;
    int Hz;
    bool running;
    string status;
	struct libwebsocket_context *context;

    static const int max_clients = 100;
    
    struct client_data {
        libwebsocket * wsi;
        list<string> outgoing_packets;
    } cd[max_clients];

    struct per_session_data__http
    {
    };

    struct per_session_data__kinf {
        int client_id;
    };

    static struct libwebsocket_protocols protocols[];

public:
    WebsocketsServer(int _Hz = 60, int _port = 7681) {
        status = "not started";

        setHz(_Hz);
        
        port = _port;
        force_exit = false;
        
        for (int i = 0; i < max_clients; i++) {
            cd[i].wsi = NULL;
        }
    }

    int callback_kinf(struct libwebsocket_context *context,
		struct libwebsocket *wsi,
		enum libwebsocket_callback_reasons reason, void *user,
							   void *_in, size_t len);

    int callback_http(struct libwebsocket_context *context,
		struct libwebsocket *wsi,
		enum libwebsocket_callback_reasons reason, void *user,
							   void *_in, size_t len);

    void setHz(int _Hz)
    {
        Hz = _Hz;
    }
    
    int getHz()
    {
        return Hz;
    }
    
    bool start();
    void stop();
    
    bool send_packet(int client, string payload)
    {
        if (cd[client].wsi == NULL) return false;
        
        if (cd[client].outgoing_packets.size() > 1000) return false;

        cd[client].outgoing_packets.push_back(payload);
    
        libwebsocket_callback_on_writable(context, cd[client].wsi);
        
        return true;
    }
    
    string getStatus() { return status; }
    
    void enterLoop()
    {
        int n = 0;
        while (n >= 0 && !force_exit) {
            struct timeval tv;
    
            gettimeofday(&tv, NULL);
    
            n = libwebsocket_service(context, 1000 / Hz);
        }
    }
    
    void exitLoop();
    
    void closeConnection(int);
    
    virtual void connectionEstablished(int) = 0;
    virtual void connectionClosed(int) = 0;
    virtual void receivedData(int, string) = 0;
};

#endif /* __WEBSOCKETS_SERVER__ */
