#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <signal.h>
#include <syslog.h>

#include "libwebsockets.h"
#include <atomic>
using namespace std;

#include "WebsocketsServer.h"

// Przestrzeń nazw KinfServer to po prostu kopia
// kinf/network/websockets/server.cpp
// z kilkoma zmianami:
// 1. int main() nie przyjmuje argumentów
// 2. dodano obiekt atomic<bool> is_running
// 3. główna pętla w main() kończy się w gdy !is_running
// 4.

namespace KinfServer
{

    atomic<bool> have_to_run(false); /// nowy obiekt
    atomic<bool> is_running(false); /// nowy obiekt

    /*
     * Based on libwebsockets-test-server
     * Copyright (C) 2010-2011 Andy Green <andy@warmcat.com>
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

    static int close_testing;
    int max_poll_elements;

    struct pollfd *pollfds;
    int *fd_lookup;
    int count_pollfds;
    int force_exit = 0;

    enum demo_protocols {
        /* always first */
        PROTOCOL_HTTP = 0,

        PROTOCOL_LWS_MIRROR,

        /* always last */
        DEMO_PROTOCOL_COUNT
    };

    struct per_session_data__http
    {
    };

    static int callback_http(struct libwebsocket_context *context,
            struct libwebsocket *wsi,
            enum libwebsocket_callback_reasons reason, void *user,
                                   void *in, size_t len)
    {
        return 0;
    }


    /* lws-mirror_protocol */

    struct per_session_data__lws_mirror {
        struct libwebsocket *wsi;
        int ringbuffer_tail;
    };

    struct a_message {
        void *payload;
        size_t len;
    };

    static struct a_message ringbuffer[WebsocketsServer::MAX_MESSAGE_QUEUE];
    static int ringbuffer_head;

    static struct libwebsocket *wsi_choked[20];
    static int num_wsi_choked;

    static int
    callback_lws_mirror(struct libwebsocket_context *context,
                struct libwebsocket *wsi,
                enum libwebsocket_callback_reasons reason,
                               void *user, void *in, size_t len)
    {
        int n;
        struct per_session_data__lws_mirror *pss = (struct per_session_data__lws_mirror *)user;

        switch (reason) {

        case LWS_CALLBACK_ESTABLISHED:
            lwsl_info("callback_lws_mirror: "
                             "LWS_CALLBACK_ESTABLISHED\n");
            pss->ringbuffer_tail = ringbuffer_head;
            pss->wsi = wsi;
            break;

        case LWS_CALLBACK_PROTOCOL_DESTROY:
            lwsl_notice("mirror protocol cleaning up\n");
            for (n = 0; n < sizeof ringbuffer / sizeof ringbuffer[0]; n++)
                if (ringbuffer[n].payload)
                    free(ringbuffer[n].payload);
            break;

        case LWS_CALLBACK_SERVER_WRITEABLE:
            if (close_testing)
                break;
            while (pss->ringbuffer_tail != ringbuffer_head) {

                n = libwebsocket_write(wsi, (unsigned char *)
                       ringbuffer[pss->ringbuffer_tail].payload +
                       LWS_SEND_BUFFER_PRE_PADDING,
                       ringbuffer[pss->ringbuffer_tail].len,
                                    LWS_WRITE_TEXT);
                if (n < 0) {
                    lwsl_err("ERROR %d writing to mirror socket\n", n);
                    return -1;
                }

                if (pss->ringbuffer_tail == (WebsocketsServer::MAX_MESSAGE_QUEUE - 1))
                    pss->ringbuffer_tail = 0;
                else
                    pss->ringbuffer_tail++;

                if (((ringbuffer_head - pss->ringbuffer_tail) &
                      (WebsocketsServer::MAX_MESSAGE_QUEUE - 1)) == (WebsocketsServer::MAX_MESSAGE_QUEUE - 15)) {
                    for (n = 0; n < num_wsi_choked; n++)
                        libwebsocket_rx_flow_control(wsi_choked[n], 1);
                    num_wsi_choked = 0;
                }
                // lwsl_debug("tx fifo %d\n", (ringbuffer_head - pss->ringbuffer_tail) & (WebsocketsServer::MAX_MESSAGE_QUEUE - 1));

                if (lws_send_pipe_choked(wsi)) {
                    libwebsocket_callback_on_writable(context, wsi);
                    return 0;
                }
            }
            break;

        case LWS_CALLBACK_RECEIVE:

            if (((ringbuffer_head - pss->ringbuffer_tail) &
                      (WebsocketsServer::MAX_MESSAGE_QUEUE - 1)) == (WebsocketsServer::MAX_MESSAGE_QUEUE - 1)) {
                lwsl_err("dropping!\n");
                goto choke;
            }

            if (ringbuffer[ringbuffer_head].payload)
                free(ringbuffer[ringbuffer_head].payload);

            ringbuffer[ringbuffer_head].payload =
                    malloc(LWS_SEND_BUFFER_PRE_PADDING + len +
                              LWS_SEND_BUFFER_POST_PADDING);
            ringbuffer[ringbuffer_head].len = len;
            memcpy((char *)ringbuffer[ringbuffer_head].payload +
                          LWS_SEND_BUFFER_PRE_PADDING, in, len);
            if (ringbuffer_head == (WebsocketsServer::MAX_MESSAGE_QUEUE - 1))
                ringbuffer_head = 0;
            else
                ringbuffer_head++;

            if (((ringbuffer_head - pss->ringbuffer_tail) &
                      (WebsocketsServer::MAX_MESSAGE_QUEUE - 1)) != (WebsocketsServer::MAX_MESSAGE_QUEUE - 2))
                goto done;

    choke:
            if (num_wsi_choked < sizeof wsi_choked / sizeof wsi_choked[0]) {
                libwebsocket_rx_flow_control(wsi, 0);
                wsi_choked[num_wsi_choked++] = wsi;
            }

    //		lwsl_debug("rx fifo %d\n", (ringbuffer_head - pss->ringbuffer_tail) & (WebsocketsServer::MAX_MESSAGE_QUEUE - 1));
    done:
            libwebsocket_callback_on_writable_all_protocol(
                               libwebsockets_get_protocol(wsi));
            break;

        default:
            break;
        }

        return 0;
    }


    /* list of supported protocols and callbacks */

    static struct libwebsocket_protocols protocols[] = {
        /* first protocol must always be HTTP handler */

        {
            "http-only",		/* name */
            callback_http,		/* callback */
            sizeof (struct per_session_data__http),	/* per_session_data_size */
            0,			/* max frame size / rx buffer */
        },
        {
            "lws-mirror-protocol",
            callback_lws_mirror,
            sizeof(struct per_session_data__lws_mirror),
            128,
        },
        { NULL, NULL, 0, 0 } /* terminator */
    };

    void sighandler(int sig)
    {
        force_exit = 1;
    }

    static struct option options[] = {
        { "help",	no_argument,		NULL, 'h' },
        { "debug",	required_argument,	NULL, 'd' },
        { "port",	required_argument,	NULL, 'p' },
        { "ssl",	no_argument,		NULL, 's' },
        { "interface",  required_argument,	NULL, 'i' },
        { "closetest",  no_argument,		NULL, 'c' },
    #ifndef LWS_NO_DAEMONIZE
        { "daemonize", 	no_argument,		NULL, 'D' },
    #endif
        { NULL, 0, 0, 0 }
    };

    int main()
    {
        int argc = 1; char** argv = NULL; /// linijka dodana na potrzeby funkcji async

        int n = 0;
        int use_ssl = 0;
        struct libwebsocket_context *context;
        int opts = 0;
        char interface_name[128] = "";
        const char *iface = NULL;
    #ifndef WIN32
        int syslog_options = LOG_PID | LOG_PERROR;
    #endif
        unsigned int oldus = 0;
        struct lws_context_creation_info info;

        int debug_level = 7;
    #ifndef LWS_NO_DAEMONIZE
        int daemonize = 0;
    #endif

        memset(&info, 0, sizeof info);
        info.port = 7681;

        while (n >= 0) {
            n = getopt_long(argc, argv, "ci:hsp:d:D", options, NULL);
            if (n < 0)
                continue;
            switch (n) {
    #ifndef LWS_NO_DAEMONIZE
            case 'D':
                daemonize = 1;
                #ifndef WIN32
                syslog_options &= ~LOG_PERROR;
                #endif
                break;
    #endif
            case 'd':
                debug_level = atoi(optarg);
                break;
            case 's':
                use_ssl = 1;
                break;
            case 'p':
                info.port = atoi(optarg);
                break;
            case 'i':
                strncpy(interface_name, optarg, sizeof interface_name);
                interface_name[(sizeof interface_name) - 1] = '\0';
                iface = interface_name;
                break;
            case 'c':
                close_testing = 1;
                fprintf(stderr, " Close testing mode -- closes on "
                           "client after 50 dumb increments"
                           "and suppresses lws_mirror spam\n");
                break;
            case 'h':
                fprintf(stderr, "Usage: test-server "
                        "[--port=<p>] [--ssl] "
                        "[-d <log bitfield>]\n");
                exit(1);
            }
        }

    #if !defined(LWS_NO_DAEMONIZE) && !defined(WIN32)
        /*
         * normally lock path would be /var/lock/lwsts or similar, to
         * simplify getting started without having to take care about
         * permissions or running as root, set to /tmp/.lwsts-lock
         */
        if (daemonize && lws_daemonize("/tmp/.lwsts-lock")) {
            fprintf(stderr, "Failed to daemonize\n");
            return 1;
        }
    #endif

        signal(SIGINT, sighandler);

    #ifndef WIN32
        /* we will only try to log things according to our debug_level */
        setlogmask(LOG_UPTO (LOG_DEBUG));
        openlog("lwsts", syslog_options, LOG_DAEMON);
    #endif

        /* tell the library what debug level to emit and to send it to syslog */
        lws_set_log_level(debug_level, lwsl_emit_syslog);

        lwsl_notice("libwebsockets test server - "
                "(C) Copyright 2010-2013 Andy Green <andy@warmcat.com> - "
                                "licensed under LGPL2.1\n");
    #ifdef EXTERNAL_POLL
        max_poll_elements = getdtablesize();
        pollfds = malloc(max_poll_elements * sizeof (struct pollfd));
        fd_lookup = malloc(max_poll_elements * sizeof (int));
        if (pollfds == NULL || fd_lookup == NULL) {
            lwsl_err("Out of memory pollfds=%d\n", max_poll_elements);
            return -1;
        }
    #endif

        info.protocols = protocols;
        if (!use_ssl) {
            info.ssl_cert_filepath = NULL;
            info.ssl_private_key_filepath = NULL;
        } else {
    //		info.ssl_cert_filepath = LOCAL_RESOURCE_PATH"/libwebsockets-test-server.pem";
    //		info.ssl_private_key_filepath = LOCAL_RESOURCE_PATH"/libwebsockets-test-server.key.pem";
        }
        info.gid = -1;
        info.uid = -1;
        info.options = opts;

        context = libwebsocket_create_context(&info);
        if (context == NULL) {
            lwsl_err("libwebsocket init failed\n");
            return -1;
        }

        n = 0;
        while (n >= 0 && !force_exit) {

            if(!have_to_run.load()) break; /// dodane

            struct timeval tv;

            gettimeofday(&tv, NULL);

            n = libwebsocket_service(context, 50);

            is_running.store(true); /// dodane
        }

        is_running.store(false);

        libwebsocket_context_destroy(context);

        lwsl_notice("libwebsockets-test-server exited cleanly\n");

        closelog();

        return 0;
    }
}

#include "../Error.h"

WebsocketsServer::WebsocketsServer()
{
    KinfServer::is_running.store(false);
    KinfServer::have_to_run.store(false);
}

WebsocketsServer::~WebsocketsServer()
{
    stop();
}

bool WebsocketsServer::isRunning()
{
    return KinfServer::is_running.load();
}

void WebsocketsServer::start()
{
    if (KinfServer::have_to_run.load()) return;

    KinfServer::have_to_run.store(true);
    server_thread = async(launch::async, KinfServer::main);
}

void WebsocketsServer::stop()
{
    if (!KinfServer::have_to_run.load()) return;

    KinfServer::have_to_run.store(false);
    int result = server_thread.get();
    if (result != 0) {
        throw Error(__FILE__, __LINE__, string("Funkcja KinfServer::main() zwróciła " + result));
    }
}
