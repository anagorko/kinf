#include<iostream>
using namespace std;
int main()
{
int n,w=0,t[57],r=0;
for(int i=0;i<57;i++)
	{
	t[i]=0;
	}
cin>>n;
char z[n];
cin>>z;
for(int i=0;i<n;i++)
	{
	r=z[i]-66;
	if(z[i]<91&&t[r+32]>0){w++;}
	if(z[i]>91&&t[r-32]>0){w++;}
	t[r]++;
	if(i==0){w=0;}
	}
cout<<w<<"\n";
}
