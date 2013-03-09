// (C) Jankek Bielecki
#include <iostream>
using namespace std;
int main(){

int n;
cin >> n;
long long int tab[n];
for(long long int i = 0; i < n; i++){
	cin >> tab[i];
}

for(long long int i = 0; i < n; i++){
	cout  << tab[i] * tab[i] << " ";
}

cout << endl;

for(long long int i = 0; i < n; i++){
	cout  << tab[i] * tab[i] * tab[i] << " ";
}

cout << endl;

}
	
