#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int t[n];
	int maxlicz=0, znak;
	for(int i=0;i<n;i++){
		cin>>t[i];
	}
	for(int i=0;i<n;i++){
		for(int a=i+1;a<n;a++){
			if(t[a]>t[i]){
				int zmienna=t[i];
				t[i]=t[a];
				t[a]=zmienna;
			}
		}
	}
	for(int i=0;i<n;i++){
		int licz=0;
		for(int a=i;t[i]==t[a] && a<n;a++){
			licz++;
		}
		if(licz>maxlicz){
			maxlicz=licz;
			znak=t[i];
		}
	}
	cout<<znak<<"\n";
return 0;
}
