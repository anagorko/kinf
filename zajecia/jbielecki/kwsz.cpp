// (C) Jankek Bielecki
#include <iostream>
#include <math.h>
using namespace std;
int main(){

int n;
cin >> n;
long long int tab[n];
for(long long int i = 0; i < n; i++){
	cin >> tab[i];
}

for(long long int i = 0; i < n; i++){
	cout  << pow(tab[i],2) << " ";
}

cout << endl;

for(long long int i = 0; i < n; i++){
	cout  << pow(tab[i], 3) << " ";
}

cout << endl;

}
	
