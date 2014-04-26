#include "client.h"

int client(string addr)
{

    string server = addr;
    
    if (!connect_to_server(server)) {
        cout << "Połączenie nie powiodło się." << endl; return 1;
    }

    string komunikat = "TEST";
    
    
	int n = 0;
	while (n >= 0 && !was_closed && !force_exit) {
        usleep(500000);

		n = service_websockets();

        send_packet(komunikat);
        
        string s;
        while (receive_packet(s)) {
            cout << "ODEBRAŁEM: " << s << endl;
        }
	}

    cout << "Kończę." << endl;

	libwebsocket_context_destroy(context);

	return 0;
}
