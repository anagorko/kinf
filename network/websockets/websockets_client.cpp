#include "websockets_client.h"

int main(int argc, char **argv)
{
	if (argc < 2) {
	    cout << "Podaj adres serwera" << endl; return 1;
    }

    string server = string(argv[1]);
    
    if (!connect_to_server(server)) {
        cout << "Połączenie nie powiodło się." << endl; return 1;
    }

    string komunikat = "TEST";
    
    if (argc >= 3) {
        komunikat = string(argv[2]);
    }
    
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
