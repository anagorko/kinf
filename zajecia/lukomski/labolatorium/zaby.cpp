#include<iostream>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	int k[n+1];
	int z[m+1];
	for(int i=1;i<=m;i++){
		z[i]=0;
	}
	int maxmuch=0;
	int ktomuch=1;
	for(int i=1;i<=n;i++){
		cin>>k[i];
		for(int a=m;a>0;a--){
			if(i%a==0){
				z[a]=z[a]+k[i];
				if(maxmuch<z[a]){maxmuch=z[a];ktomuch=a;}
				break;
			}
		}
	}
	cout<<ktomuch<<"\n";
	return 0;
}
