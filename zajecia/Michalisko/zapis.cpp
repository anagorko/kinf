#include<iostream>
using namespace std;

int main(){
	string lit;
	int dlug, obl = 0;
	cin >> lit;
	dlug= lit.length();
	for(int a=dlug-1; a>=0; a--){
		obl= obl+(lit[a]- 64);
	}	
	cout << obl;
}
