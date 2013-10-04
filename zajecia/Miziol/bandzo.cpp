#include<iostream>
using namespace std;
int main()
{
int n,r,r2,wp=0,w=0;
cin>>n;
int t[n*2];
for(int i=0;i<n*2;i++)
	{
	cin>>r;
	if(wp==1){t[i]=(r*2)+1;wp--;}
	else{t[i]=(r*2);wp++;}
	}

for(int i=0;i<2*n;i++)
	{
	for(int j=i+1;j<n*2;j++)
		{
		if(t[i]>t[j])
			{
			r=t[i];
			t[i]=t[j];
			t[j]=r;
			}
		}
	}

for(int i=0;i<n*2;i++)
	{
	if(t[i]%2==1){w--;}
	if(t[i]%2==0){w++;}
	}

cout<<w<<"\n";

return 0;
}
