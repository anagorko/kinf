#include<iostream>
using namespace std;
int main(){

int h;
cin>> h;
for(int i=0;i<h;i++){
	
	
	if (i==h/2){
		for(int j=0;j<h;j++){
			cout<<"H";
		}
	}
	else {
		cout<<"H";
		for(int u=0;u<h-2;u++){
			cout<<" ";
		}
		cout<<"H";
	}

cout<<endl;	
}




}

