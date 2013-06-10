#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int kop[n+1];
	for(int i=1;i<=n;i++){
		int x=i;
		cin>>kop[i];
		while(kop[x]<kop[x/2]){
			int zmienna=kop[x];
			kop[x]=kop[x/2];
			kop[x/2]=zmienna;
			x=x/2;
		}
	}
	while(n>0){
		cout<<kop[1]<<" ";
		kop[1]=kop[n];
		n--;
		int x=1;
		while(true){
			int y=0;
			if(kop[x]>kop[x*2] && kop[x]>kop[x*2+1]){
				if(kop[x*2]>kop[x*2+1]){
					y=x*2;
				}else{
					y=x*2+1;
				}
			}else if(kop[x]>kop[x*2] || kop[x]>kop[x*2+1]){
				if(kop[x]>kop[x*2]){
					y=x*2;
				}else{
					y=x*2+1;
				}
			}
			if(y==0){break;}
			int zmienna=kop[x];
			kop[x]=kop[y];
			kop[y]=zmienna;
			x=y;
		}
	}
	return 0;
}
