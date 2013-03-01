//
// Janku, sprawdź działanie programu w serwisie main.edu.pl
// Jak zaliczysz na 100% usuń ten komentarz
//

#include<iostream>
using namespace std;
int main(){
	int error = 0;
	string ajs;
	string cfaj;
	getline (cin,ajs);
	getline (cin,cfaj);


	
		for(int i= 0; i < ajs.length(); i++){

		if(cfaj[i] != ajs[i]){ error++; }}


		cout << error<<"\n";



return 0;
}
