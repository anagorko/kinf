#include<iostream>
using namespace std;
int main(){
	int t[15];
	for(int i=0;i<15;i++){
		t[i]=0;
	}
	int kon=1;
	int a;
	for(int i=0;i<15;i++){
		cin>>a;
		for(int b=0;b<kon;b++){
			if(a%37==t[b]){
				break;
			}
			if(b==kon-1 && a%37!=t[b]){
				t[kon]=a%37;
				kon++;
			}
		}
	}
	cout<<kon-1<<endl;
	return 0;
}
