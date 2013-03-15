// (C) Jankek Bielecki

#include <iostream>
#include <math.h>

using namespace std;
int main(){

int n;
cin >> n;
long  tab[n];
for(long i = 0; i < n; i++){
	cin >> tab[i];
}

for(long i = 0; i < n; i++){
	cout  << pow(tab[i],2) << " ";
}

cout << endl;

for(long i = 0; i < n; i++){
	cout  << pow(tab[i], 3) << " ";
}

cout << endl;

}
	
