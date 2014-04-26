#include "client.h"
#include <iostream>
using namespace std;
int run_server(){
	if (!connect_to_server("ubuntu")) {
        cout << "Połączenie nie powiodło się. Odpalam server\n";
        	system ("./server&"); 
        	return 1;
  	}else{
  		return 0;
  	}
}