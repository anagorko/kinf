#include <iostream>

using namespace std;

int main()
{
	int n,t;

	cin>>n;

	int p[n];

	for(int i=0; i<n; i++)
	{
		cin>>p[i];
	}

	cin>>t;

	int pod[t];
	int a,b;

	for(int i=0; i<t; i++)
	{
		cin>>a>>b;
		if(p[a-1]-p[b-1]==1 || p[b-1]==-1 && p[a-1]==1) pod[i]=1;
		else pod[i]=0;
		//if(p[b]==-1 && p[a]==1) pod[i]=1;	
	}

	for(int i=0; i<t; i++)
	{
		if(pod[i]==1) cout<<"TAK\n";
		else cout<<"NIE\n";
	}

}
