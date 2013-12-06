#include <iostream>
using namespace std;
int main (){

int t[20];
for(int j=0;j<20;j++){
cin>> t[j];
}
for(int x=0;x<2;x++){
	for(int i=0;i<20;i++){
		if(t[i]%2==x){
		cout<< t[i]<< endl;
		}
	}
}
return 0;
}
