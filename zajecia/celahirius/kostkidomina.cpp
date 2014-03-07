#include <iostream>

using namespace std;

int main()
{

int n,k=0,p=0,t,c=0;

cin>>n;

int a[2*n][2];
int b[2*n];

for(int i=0; i<2*n; i++)
{
	cin>>a[i][1];
	for(int j=0; j<2*n; j++)
	{
		if(a[i][1]==a[j][1])
		{
			a[j][2]++;
		}			
	}
}

for(int i=0; i<2*n; i++)
{
	if(a[i][2]%2!=0 && k==0)
	{
		k=a[i][1];
		c++;
	}
	else if(a[i][2]%2!=0 && p==0)
	{
		p=a[i][1];
		c++;
	}
}

if(c>2)
{
	cout<<"NIE\n";
}
else if(p>k) cout<<endl<<k<<" "<<p<<endl; 
else if(k>p) cout<<endl<<p<<" "<<k<<endl;

}
