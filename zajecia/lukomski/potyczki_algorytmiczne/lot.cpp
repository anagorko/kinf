#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	char znak;
	int t[n];
	int licz=0;
	for(int i=0;i<n;i++){
	cin>>znak;
		if(znak=='A'){t[i]=0;}
		if(znak=='B'){t[i]=1;}
		if(znak=='C'){t[i]=2;}
	}
	for(int i=1;i<n;i++){
	bool bylem=false;
		if(t[i]==t[i-1]){t[i]=10;bylem=true;}
		if(bylem){licz++;}
	}
	cout<<licz<<endl;
return 0;
}
