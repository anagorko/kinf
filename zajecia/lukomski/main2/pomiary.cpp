#include<iostream>
using namespace std;
int main(){
	int p,w=0;
	cin>>p;
	while(true){
		int a;
		cin>>a;
		if(a==-1)break;
		if(a!=p){
			w++;
			p=a;
		}
	}
	cout<<w<<endl;
} 
