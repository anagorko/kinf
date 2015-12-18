#include<iostream>
using namespace std;

int main(){
	int a, b, c;
	cin >> a;
	a=a/3;
	b=a-1;
	c=a+1;
	if(a<b & a<c)
		cout <<a;
	if(b<a & b<c)
		cout <<b;
	if(c<a & c<b)
		cout <<c;
}
