#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	long long int t[n];
	int kon=n;
	for(int i=0;i<n;i++){
		cin>>t[i];
	}
	for(int i=0;i<n;i++){
		for(int a=0;a<kon-1;a++){
			t[a]=t[a]+t[a+1];
			t[a]=t[a]%1000000033;
		}
	kon--;
	}
cout<<t[0];
return 0;
}

