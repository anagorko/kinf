#include<iostream>
using namespace std;
int main()
{
int n,r,ru;
cin>>n;
int t[n];
for(int i=0;i<n;i++){cin>>t[i];}

for(int i=0;i<n;i++)
	{
	for(int j=i+1;j<n;j++)
		{
		if(t[i]>t[j])
			{
			r=t[i];
			t[i]=t[j];
			t[j]=r;
			}
		}
	}

for(int i=0;i<n;i++)
	{
	cout<<t[i]<<" ";
	}
cout<<"\n";

return 0;
}
