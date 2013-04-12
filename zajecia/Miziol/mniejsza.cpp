#include<iostream>
using namespace std;
int mniejsza(int a, int b)
	{
	if(a>b){return b;}
	if(a<b){return a;}
	}
int main()
	{
	int a,b;
	cin>>a;
	cin>>b;
	cout<<mniejsza(a,b);
	return 0;
}
