//(c) by Janke Kacprzak

#include <stdlib.h>
#include <iostream>
using namespace std;

int main()
{
  srandom(time(NULL)+getpid());
int los = 0;
     cout << "Orzeł czy reszka: \n";
  for (int i = 0; i < 20; i++) {
	los = random() % 2;	
	if (los == 0) cout<< "R\n"; 
	else cout << "O\n";
     	
  }
  cout << endl;	
    return 0;
}

