#include<iostream>
using namespace std;
int main()
{
int n,a,b;
cin>>n;
a=n-1;
b=1;
for(int i=0;i<n;i++)
	{
	for(int j=0;j<a;j++)
		{
		cout<<".";
		}
	for(int j=0;j<b;j++)
		{
		cout<<"A";
		}
		a--;
		b=b+2;
		cout<<"\n";
	}
for(int i=0;i<n-2;i++)
	{
	cout<<".";
	}
cout<<"HHH\n";
return 0;
}
