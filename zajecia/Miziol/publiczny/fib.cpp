#include<iostream>
using namespace std;
int fib(int n)
	{
	int a,b,c;
	c=0;
	b=1;
	for(int i=0;i<n;i++)
		{
		a=b+c;
		c=b;
		b=a;
		}
	return a;
	}
int main()
{
int n;
cin>>n;
cout<<fib(n);
return 0;
}
