#include<iostream>
using namespace std;
int main()
{
int n,r=2;
cin>>n;
if(n==0)cout<<1<<"\n";
if(n==1)cout<<2<<"\n";
else
	{
	for(int i=0;i<n;i++)
		{
		r=r*2;
		if(r>1000000000||r<0)break;
		cout<<r<<"\n";
		}
	}

return 0;
}
