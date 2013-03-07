// (C) Janek Bielecki
#include <iostream>
using namespace std;

int main() {

int ile;		//ile każde dziecko zebrało dango dnia 
int n;
int ile_dzieci;
int suma;

cin >> ile_dzieci;
	
int wynik[ile_dzieci]; //tablica wyników 

for (int j = 0; j < ile_dzieci; j++) {
  
	suma = 0;
	cin >> n;
	for (int i=0; i < n; i++){
    	
	cin >> ile;
	suma =  suma + ile;

	}
	
	wynik[j] = suma;
}
for (int i=0; i < ile_dzieci; i++){

cout << wynik[i] << endl; 

}
}
