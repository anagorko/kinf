#include <iostream>
using namespace std;


void kreski(int n, string s){
	for (int i=0; i<n; i++){
		cout << s;
	}
}
void kreskiq() {
	{cout<< "               _/||\\_"<<endl;}
	{cout<< "            _/:::||:::\\_"<<endl;}
	{cout<< "        _/:::::::||::::::\\_"<<endl;}
	{cout<< "     _/::::::::::||:::::::::\\_"<<endl;}
	{cout<<"    |\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|"<<endl;}
}
void slasze(){
	{cout<<"     \\_/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\_/"<<endl;}
	{cout<<"       \\_/\\/\\/\\/\\/\\/\\/\\/\\/\\_/"<<endl;}
	{cout<<"         \\_/\\/\\/\\/\\/\\/\\/\\_/"<<endl;}
	{cout<<"           \\_/\\/\\/\\/\\/\\_/"<<endl;}
}


void pien(int w, string d){
	for (int e=0; e<w; e++) {
		cout<< d;
	}
}
int main(){
	
	kreski(4, "                 ||\n");
	kreskiq();
	slasze();
	kreski(4, "                 ||\n");
	pien(10 , "              |%%||%%|\n");
	kreskiq();
	return 0;
}
	

