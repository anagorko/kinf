#include<iostream>
#include<string>
using namespace std;

int main(){
	string liczba;
	cin >> liczba;
	int a;
	a= liczba.length();
	for(int i=a; i>=0; i--){
		cout << liczba[i];
	}
} 
