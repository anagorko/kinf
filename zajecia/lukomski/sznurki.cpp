#include<iostream>
using namespace std;
int main(){
	int n,w;
	cin>>n>>w;
	int licznik=0;
	int suma=0;
	for(int i=0;i<n;i++){
		int t;
		cin>>t;
		suma=suma+t;
		if(suma>=w){
			suma=0;
			licznik++;
		}
	}
	cout<<licznik<<"\n";
	return 0;
	}
