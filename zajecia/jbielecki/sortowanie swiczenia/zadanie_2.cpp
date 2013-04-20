#include <iostream>
using namespace std;
int main(){
int n;
cin >> n;
int tab[n];
	for(int i = 0; i < n; i++){
		cin >> tab[i];
	}
	for(int i = n; i >= 0; i--){
		if(tab[i] == tab[i - 1])
		cout << tab[i] << " ";
	}
cout << endl;
return 0;
}
