#include<iostream>
using namespace std;
int main()
{
int n,r,ru;
cin>>n;
int t[n],w[n],ww[2];
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
r=0;
for(int i=0;i<n;i++)
	{
	if(w[i]>ww[0]){ww[1]=i;ww[0]=w[i];}
	}
cout<<ww[1];
cout<<"\n";

return 0;
}
