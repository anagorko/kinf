#include<iostream>
using namespace std;
int main(){
	int n;
	int m;
	cin>>n>>m;
	int t[n];
	for(int i=0;i<n;i++){t[i]=0;}
	for(int i=0;i<m;i++){
		int p;
		cin>>p;
		if(p<=n){t[p-1]++;}
		if(p==n+1){
			int max=0;
			for(int a=0;a<n;a++){
				if(t[a]>max){max=t[a];}
			}
			for(int a=0;a<n;a++){t[a]=max;}
		}
	}
	for(int i=0;i<n;i++){
	cout<<t[i]<<" ";
	}
	cout<<endl;
}
