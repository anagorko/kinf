#include<iostream>
using namespace std;
int main(){
	int min0=101;
	int min1=101;
	for(int i=0;i<10;i++){
		int a;
		cin>>a;
		if(a<min0){
			min1=min0;
			min0=a;
		}else if(a<min1){
			min1=a;
		}
	}
	cout<<min0<<" "<<min1<<"\n";
	return 0;
}
