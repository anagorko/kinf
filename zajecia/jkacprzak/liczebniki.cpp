// (c) copyright by Janek Kacprzka

#include<iostream>
#include<string>
using namespace std;
int main (){
int x, n, s;
cin >> x;
n = x;
s = x;
string dwa = "trololo";
int k;
for (k = 0; s = 0;k++ ) {s = s/10;}
for (int i = 0; i <= k;i++){
	x = x % 10; 
	cout << x<< endl;
	if (x = 9){dwa = "dziewięć";}	
	if (x = 8){dwa = "osiem";}
	if (x = 7){dwa = "siedem";}
	if (x = 6){dwa = "sześć";}
	if (x = 5){dwa = "pięć";}
	if (x = 4){dwa = "cztery";}
	if (x = 3){dwa = "trzy";}
	if (x = 2){dwa = "dwa";}
	if (x = 1){dwa = "jeden";}
}
cout << dwa<< endl;
return 0;
}
