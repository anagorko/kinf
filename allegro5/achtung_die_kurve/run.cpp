#include "client.h"
#include <iostream>
using namespace std;
int run_server(){
	cout<<"jestem w runie\n";
	if (!connect_to_server("ubuntu")) {
        cout << "Połączenie nie powiodło się. Odpalam server\n";
        	system ("./server&");
        	usleep(4000);
        	connect_to_server("ubuntu"); 
        	return 1;
  	}else{
  		return 0;
  	}
}