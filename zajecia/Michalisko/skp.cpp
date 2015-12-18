#include<iostream>
using namespace std;

int main(){
	int a, b= 0, c= 0;
	cin >> a;
	for(int i= 0; i < 5;i++){
		b=b+a+c;
		c=c+2;
	}
	cout << b;
}
