#include<iostream>
using namespace std;
int main()
{
int n,r,ru;
cin>>n;
int t[n],w[n];
for(int i=0;i<n;i++){w[i]=0;}
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
	w[t[i]]++;
	}
for(int i=0;i<n;i++)
	{
	if(w[i]>1){cout<<i<<" ";}
	}
cout<<"\n";

return 0;
}
