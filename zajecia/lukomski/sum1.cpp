#include<iostream>
using namespace std;
int main(){
	int a,suma=0,max=0;
	while(!cin.eof()){
		cin>>a;
		suma=suma+a;
		if(suma>max){max=suma;}
		if(suma<0){suma=0;}
	a=0;
	}
cout<<max<<endl;
return 0;
}
