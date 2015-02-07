#include <iostream>
using namespace std;

bool czy_rowne(string a, string b){
	if(a.length() != b.length()) return false;
	for(int i=0; i<a.length(); i++){
		if(a[i] != b[i]) return false;
	}
	return true;
}
bool czy_a_mniejsza(string a, string b){
	if(a.length() > b.length()) return false;
	if(a.length() < b.length()) return true;
	for(int i=0; i<a.length(); i++){
		if(a[i] < b[i]) return true;
	}
	return false;
}

int main(){

	bool wynik = 0;
	string a,b,dzialanie;
	cin>>a>>dzialanie>>b;	

	if(dzialanie == "=="){

		wynik = czy_rowne(a,b);

	}else if(dzialanie == "!="){
		wynik = !czy_rowne(a,b);
	}else if(dzialanie == "<"){
		wynik = czy_a_mniejsza(a,b);
	}else if(dzialanie == ">"){
		wynik = !czy_a_mniejsza(a,b) && !czy_rowne(a,b);
	}else if(dzialanie == "<="){
		wynik = czy_a_mniejsza(a,b) || czy_rowne(a,b);
	}else if(dzialanie == ">="){
		wynik = !czy_a_mniejsza(a,b) || czy_rowne(a,b);
	}

	if(wynik == 0){
		cout<<"NIE\n";
	}else{
		cout<<"TAK\n";
	}
}
