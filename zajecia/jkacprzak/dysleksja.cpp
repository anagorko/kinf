//
// Janku, ten program się nawet nie kompiluje :)
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
