#include<iostream>
using namespace std;
int main()
{
int d;
cin>>d;
int t[d],w=0,n=0,dn=0;

for(int i=0;i<d;i++)
	{
	cin>>dn; w = 0;
	for(int j=0;j<dn;j++)
		{
		cin>>n;
		w=w+n;
		}
	t[i]=w;
	}
for(int k=0;k<d;k++)
	{
	cout<<t[k]<<"\n";
	}

return 0;
}
