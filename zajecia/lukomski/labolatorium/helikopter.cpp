#include<iostream>
using namespace std;
int main(){
	int d;
	cin>>d;
	for(int i=1;i<=d;i++){
		if(i!=d/2+1){
			cout<<"H";
			for(int a=0;a<d-2;a++){
				cout<<" ";
			}
			cout<<"H\n";
		}else{
			for(int a=0;a<d;a++){
				cout<<"H";
			}
			cout<<"\n";
		}
	}
	return 0;
	}
