#include<iostream>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	int schody[n];
	int max=0;
	for(int i=0;i<n;i++){
		cin>>schody[i];
		if(schody[i]>max){max=schody[i];}
		if(schody[i]<max){schody[i]=max;}
	}
	for(int i=0;i<m;i++){
		int wzrost;
		cin>>wzrost;
		for(int a=0;a<n;a++){
			if(wzrost<=schody[a]){cout<<a<<" ";break;}
			if(a==n-1){cout<<n<<" ";}
		}
	}
	cout<<"\n";
	return 0;
	}
