#include<iostream>
using namespace std;
int main()
{
int n;
int t[30000];
int e=0;
cin>>n;
for(int i=1;i*i<=n;i++)
	{
	if(n%i==0)
		{
		cout<<i<<"\n";
		t[e]=i;
		e++;
		}
	}
e--;
if (n/t[e] == t[e]) { e--; }
for(;e>=0;e--)
	{
	cout<<n/t[e]<<"\n";
	}
return 0;
}
