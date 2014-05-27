#include<iostream>
#include<set>
using namespace std;

#include "websockets_server.h"

bool WebsocketsServer::force_exit;

void sighandler(int sig)
{
    WebsocketsServer::force_exit = true;
}

int WebsocketsServer::_callback_kinf(struct libwebsocket_context *context,
    struct libwebsocket *wsi,
    enum libwebsocket_callback_reasons reason, void *user,
                           void *_in, size_t len)
{
    WebsocketsServer *_this = (WebsocketsServer*) libwebsocket_context_user(context);

    return _this -> callback_kinf(context, wsi, reason, user, _in, len);
}

int WebsocketsServer::_callback_http(struct libwebsocket_context *context,
    struct libwebsocket *wsi,
    enum libwebsocket_callback_reasons reason, void *user,
                           void *_in, size_t len)
{
    WebsocketsServer *_this = (WebsocketsServer*) libwebsocket_context_user(context);

    return _this -> callback_http(context, wsi, reason, user, _in, len);
}



struct libwebsocket_protocols WebsocketsServer::protocols[] = {
    /* first protocol must always be HTTP handler */

    {
        "http-only",		/* name */
        WebsocketsServer::_callback_http,		/* callback */
        sizeof (struct per_session_data__http),	/* per_session_data_size */
        0,			/* max frame size / rx buffer */
    },
    {
        "kinf-protocol",
        WebsocketsServer::_callback_kinf,
        sizeof(struct per_session_data__kinf),
        128,
    },
    { NULL, NULL, 0, 0 } /* terminator */
};

bool WebsocketsServer::start()
{

	struct lws_context_creation_info info;

	memset(&info, 0, sizeof info);
	info.port = port;

    signal(SIGINT, sighandler);

	info.protocols = protocols;

	info.gid = -1;
	info.uid = -1;
	info.user = this;
	
	context = libwebsocket_create_context(&info);
	if (context == NULL) {
		lwsl_err("libwebsocket init failed\n");
		return false;
	}
		
    return true;	    
}

void WebsocketsServer::stop()
{
	libwebsocket_context_destroy(context);

	lwsl_notice("libwebsockets-test-server exited cleanly\n");
}

int WebsocketsServer::callback_http(struct libwebsocket_context *,
		struct libwebsocket *,
		enum libwebsocket_callback_reasons reason, void *,
							   void *_in, size_t len)
{
    return 0;
}

int WebsocketsServer::callback_kinf(struct libwebsocket_context *context,
			struct libwebsocket *wsi,
			enum libwebsocket_callback_reasons reason,
					       void *user, void *in, size_t len)
{
	unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + 4096 +
						  LWS_SEND_BUFFER_POST_PADDING];
	int l = 0;
	int n;
    
	switch (reason) {

	case LWS_CALLBACK_CLOSED:
		{

	    int client_id = ((per_session_data__kinf*) user) -> client_id;
        connectionClosed(client_id);
        }
        
		break;

	case LWS_CALLBACK_ESTABLISHED:
        {
        int i;
                
        for (i = 0; i < max_clients; i++) {
            if (cd[i].wsi == NULL) break;
        }
        
        if (i == max_clients) return -1;

        ((per_session_data__kinf*) user) -> client_id = i;
        cd[i].wsi = wsi;

        connectionEstablished(i);
        
		libwebsocket_callback_on_writable(context, wsi);
		}
		break;

	case LWS_CALLBACK_RECEIVE:
	    receivedData(((per_session_data__kinf*) user) -> client_id, string((char *) in, len));
		break;

	case LWS_CALLBACK_SERVER_WRITEABLE:
	    {
	    int client_id = ((per_session_data__kinf*) user) -> client_id;
	    
        if (cd[client_id].outgoing_packets.empty()) break;
                
        string p = cd[client_id].outgoing_packets.front();
        cd[client_id].outgoing_packets.pop_front();
        
        l += sprintf((char*)&buf[LWS_SEND_BUFFER_PRE_PADDING+l], "%s", p.c_str());

		libwebsocket_write(wsi,
		   &buf[LWS_SEND_BUFFER_PRE_PADDING], l, LWS_WRITE_TEXT);

		libwebsocket_callback_on_writable(context, wsi);
	    }
	    break;
	default:
		break;
	}

	return 0;
}

