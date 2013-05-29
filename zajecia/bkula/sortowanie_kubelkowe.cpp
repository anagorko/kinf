#include <iostream>
using namespace std;
int main (){

int n;
int k[1000000];

for (int i = 0; i != 1000000; i++) k[i] = 0;

cout<<"Ile liczb chcesz posortować?"<<endl;
cin>>n;
int l[n];
cout<<"Wypisz liczby do posortowania"<<endl;

for (int i = 0; i != n; i++){
	cin>>l[i];
}

for (int i = 0; i != n; i++){
	k[l[i]]++;
}

for (int i = 0; i != 1000000;){
	if (k[i] != 0){
		cout<<i<<" ";
		k[i]--;
	}
	else i++;
}

return 0;
}
