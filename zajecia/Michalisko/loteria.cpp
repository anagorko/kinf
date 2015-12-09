#include<iostream>
using namespace std;

int main(){
	int a, c= 1;
	cin >> a;
	cout << c << " ";
	for(int i=((a-1)/2)-1; i>=0; i--){
		c=c+3;
		cout << c << " ";
		c=c-2;
		cout << c << " ";
	}
}
