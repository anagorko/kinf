#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;
int main (){

int s = 0;
int t;
int k;
string p;
bool komp;

cout<<"Do ilu gramy? (zakres 20-100) ";
cin>>k;
cout<<"Kto ma zaczynać? (ja/komp) ";
cin>>p;

if (p == "ja"){
	cout<<"+ ";
	cin>>t;
	if (t < 6) s += t;
}

for (int i = 0; k != s; i++){
	if ((i % 2) == 1){
		cout<<"+ ";
		cin>>t;
		if (t < 6) s += t;
		if (i != 1) cout<<"= "<<s<<endl;
		komp = false;
	} else {
		if (((k - s) % 6) == 0) t = 1;
		else t = ((k - s) % 6);
		cout<<"+ "<<t<<endl;
		if (t < 6) s += t;
		usleep(40);
		if (i != 1) cout<<"= "<<s<<endl;
		komp = true;
	}
}

if (komp == true) cout<<"Porażka!";
else cout<<"Zwycięstwo!";
cout<<endl;

return 0;
}
