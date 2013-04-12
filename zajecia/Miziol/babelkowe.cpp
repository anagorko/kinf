#include<iostream>
using namespace std;
int main()
{
int n,r,ru;
cin>>n;
int t[n];
for(int i=0;i<n;i++){cin>>t[i];}
for(;;)
	{
	for(int i=0;i<n;i++)
		{
		if(t[i]>t[i+1])
			{
			ru++;
			r=t[i];
			t[i]=t[i+1];
			t[i+1]=r;
			}
		}
	if(ru>0){break;}
	ru=0;
	}
for(int i=0;i<n;i++)
	{
	cout<<t[i]<<" ";
	}
cout<<"\n";

return 0;
}
