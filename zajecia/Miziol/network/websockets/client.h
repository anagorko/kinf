/*
 * Based on libwebsockets-test-client
 * Copyright (C) 2011 Andy Green <andy@warmcat.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation:
 *  version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#include<list>
#include<string>
#include<iostream>
using namespace std;

list<string> outgoing_packets;
list<string> incoming_packets;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>

#include "libwebsockets.h"

static unsigned int opts;
static int was_closed;
static int deny_deflate;
static int deny_mux;
static struct libwebsocket *wsi_mirror;
static int mirror_lifetime = 0;
static int force_exit = 0;


/*
 * This demo shows how to connect multiple websockets simultaneously to a
 * websocket server (there is no restriction on their having to be the same
 * server just it simplifies the demo).
 *
 *  dumb-increment-protocol:  we connect to the server and print the number
 *				we are given
 *
 *  lws-mirror-protocol: draws random circles, which are mirrored on to every
 *				client (see them being drawn in every browser
 *				session also using the test server)
 */

enum demo_protocols {

	PROTOCOL_LWS_MIRROR,

	/* always last */
	DEMO_PROTOCOL_COUNT
};


/* lws-mirror_protocol */


static int
callback_lws_mirror(struct libwebsocket_context *context,
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
		fprintf(stderr, "mirror: LWS_CALLBACK_CLOSED\n");
		wsi_mirror = NULL;
		break;

	case LWS_CALLBACK_CLIENT_ESTABLISHED:

		/*
		 * start the ball rolling,
		 * LWS_CALLBACK_CLIENT_WRITEABLE will come next service
		 */

		libwebsocket_callback_on_writable(context, wsi);
		break;

	case LWS_CALLBACK_CLIENT_RECEIVE:
	    incoming_packets.push_back(string((char *) in, len));
		break;

	case LWS_CALLBACK_CLIENT_WRITEABLE:
        if (outgoing_packets.empty()) break;
                
        while (!outgoing_packets.empty()) {
            string p = outgoing_packets.front();
            outgoing_packets.pop_front();
            
            l += sprintf((char*)&buf[LWS_SEND_BUFFER_PRE_PADDING+l], "%s", p.c_str());
        }

		libwebsocket_write(wsi,
		   &buf[LWS_SEND_BUFFER_PRE_PADDING], l, LWS_WRITE_TEXT);

		libwebsocket_callback_on_writable(context, wsi);
	default:
		break;
	}

	return 0;
}


/* list of supported protocols and callbacks */

static struct libwebsocket_protocols protocols[] = {
	{
		"lws-mirror-protocol",
		callback_lws_mirror,
		0,
		128,
	},
	{ NULL, NULL, 0, 0 } /* end */
};

void sighandler(int sig)
{
	force_exit = 1;
}



struct libwebsocket_context *context;

bool send_packet(string payload)
{
    if (outgoing_packets.size() > 1000) return false;
    
    outgoing_packets.push_back(payload);

	libwebsocket_callback_on_writable(context, wsi_mirror);
    
    return true;
}

bool receive_packet(string &payload)
{
    if (incoming_packets.empty()) return false;
    
    payload = incoming_packets.front();
    incoming_packets.pop_front();
    
    return true;
}

int service_websockets()
{
    return libwebsocket_service(context, 0);
}

bool connect_to_server(string address)
{
	int n = 0;
	int ret = 0;
	int port = 7681;
	int use_ssl = 0;

	int ietf_version = -1; /* latest */
	int longlived = 0;
	struct lws_context_creation_info info;

	memset(&info, 0, sizeof info);
    
	signal(SIGINT, sighandler);

	/*
	 * create the websockets context.  This tracks open connections and
	 * knows how to route any traffic and which protocol version to use,
	 * and if each connection is client or server side.
	 *
	 * For this client-only demo, we tell it to not listen on any port.
	 */

	info.port = CONTEXT_PORT_NO_LISTEN;
	info.protocols = protocols;
	info.gid = -1;
	info.uid = -1;

	context = libwebsocket_create_context(&info);
	if (context == NULL) {
		fprintf(stderr, "Creating libwebsocket context failed\n");
		return 1;
	}
    wsi_mirror = libwebsocket_client_connect(context,
        address.c_str(), port, use_ssl,  "/",
        address.c_str(), address.c_str(),
        protocols[PROTOCOL_LWS_MIRROR].name, ietf_version);

    if (wsi_mirror == NULL) {
        fprintf(stderr, "libwebsocket "
                      "mirror protocol connect failed\n");
    	libwebsocket_context_destroy(context);
        return false;
    }

    return true;
}
