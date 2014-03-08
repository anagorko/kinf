#include <iostream>

using namespace std;

int main()
{

int n,t,c=0;
int p=0;
int k=0;
cin>>n;

int a[2*n][2];
int b[2*n];

for(int x=0; x<2*n; x++)
{
	a[x][1]=0;
}

for(int i=0; i<2*n; i++)
{
	cin>>b[i];
	for(int j=0; j<2*n; j++)
	{
		if(a[j][1]==0) 
		{
			a[j][1]=b[i];
			a[j][2]=1;
			break;
		}
		if(a[j][1]==b[i])
		{
			a[j][2]++;
			break;
		}
	}
}

for(int i=0; i<2*n; i++)
{
	if(a[i][2]!=0)
	{
		if(a[i][2]%2!=0 && p==0)
		{
			p=a[i][1];
		}
		else if(a[i][2]%2!=0 && k==0)
		{
			k=a[i][1];
		}
	}
}

if(c>2)
{
	cout<<"NIE\n";
}
else if(k<p) cout<<endl<<k<<" "<<p<<endl; 
else if(p<k) cout<<endl<<p<<" "<<k<<endl;

}
