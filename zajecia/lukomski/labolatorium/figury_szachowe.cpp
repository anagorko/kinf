#include<iostream>
using namespace std;
int main(){
	for(int i=0;i<6;i++){
		int a;
		cin>>a;
		if(i<2){
			cout<<1-a<<" ";
		}else if(i<5){
			cout<<2-a<<" ";
		}else if(i==5){
			cout<<8-a<<"\n";
		}
	}
	return 0;
}	
