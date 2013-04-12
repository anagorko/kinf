#include<iostream>
using namespace std;
int main()
{
int n,rn;
cin>>n;
rn=n-1;
int t[n];
for(int i=0;i<n;i++)
	{
	cin>>t[i];
	}
for(int i=0;i<n-1;i++)
	{
	for(int j=0;j<rn;j++)
		{
		t[j]=(t[j]+t[j+1])%1000000033;
		}
	rn--;
	}
cout<<t[0]<<"\n";

return 0;
}
