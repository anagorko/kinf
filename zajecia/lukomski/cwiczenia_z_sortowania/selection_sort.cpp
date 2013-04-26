#include<iostream>
using namespace std;
int main(){
	cout<<"wpisz dlugosc ciagu: ";
	int n;
	cin>>n;
	cout<<"wpisz ciag: ";
	int t[n];
	for(int i=0;i<n;i++){
		cin>>t[i];
	}
	int zmienna;
	for(int i=0;i<n;i++){
		for(int a=0;a<n;a++){
			if(t[a]>t[i]){
				zmienna=t[a];
				t[a]=t[i];
				t[i]=zmienna;
			}
		}
	}
	for(int i=0;i<n;i++){
	cout<<t[i]<<" ";
	}
	cout<<"\n";
return 0;
}
