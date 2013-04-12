#include<iostream>
using namespace std;
int main()
{

int n,k=0;
int s[1000000],p[1000000];
cin>>n;
for (int i=0 ; i<n ; i++)
	{
	cin>>s[i];
	}
for (int i=0; i<n ; i++)
	{
	cin>>p[i];
		if ( p[i]<s[i]) {k++;}
		if ( p[i]>s[i]) {}
		if ( p[i]==s[i]) {}
	}
cout<<k<<"\n";

return 0;
}
