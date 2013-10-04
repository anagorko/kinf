#include "client.h"

int main(int argc, char **argv)
{
	if (argc < 2) {
	    cout << "Podaj adres serwera" << endl; return 1;
    }

    string server = string(argv[1]);
    
    if (!connect_to_server(server)) {
        cout << "Połączenie nie powiodło się." << endl; return 1;
    }
    
    if (argc < 3) {
        cout << "Podaj swój nick" << endl; return 1;
    }
    
    string nick = string(argv[2]);
    
	int n = 0;
	while (n >= 0 && !was_closed && !force_exit) {
        cout << "? ";
        string komunikat;
        cin >> komunikat;

        send_packet(nick + ": " + komunikat);
        
		n = service_websockets();
        
        string s;
        while (receive_packet(s)) {
            cout << s << endl;
        }
	}

    cout << "Kończę." << endl;

	libwebsocket_context_destroy(context);

	return 0;
}
