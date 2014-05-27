#include<iostream>
using namespace std;
int nwd(int a, int b){
	while(a!=0 && b!=0){
		if(a>b){
			a=a%b;
		}else{
			b=b%a;
		}

	}
	if(a==0){
		return b;
	}else{
		return a;
	}
}
int nww(int a,int b){
	a=(a*b)/(nwd(a,b));
	return a;
}
int main(){
	int z;
	cin>>z;
	int t[z][2];
	for(int i=0;i<z;i++){
		cin>>t[i][0];
		cin>>t[i][1];
	}
	int w=nww(t[0][1],t[0][1]);
	for(int i=2;i<z;i++){
		w=nww(t[i][1],w);
	}
	cout<<"w="<<w<<"\n";
	float l=0;
	int s=0;
	for(int i=0;i<z;i++){
		int d=w/t[i][1];
		int s=s+t[i][0]*d;
	}
	l=s/w;
	cout<<l+1<<"\n";
	return 0;
}
