#include<iostream>
using namespace std;
int main()
{
int n;
cin>>n;
int l[n];
for(int i=0;i<n;i++){l[i]=i;}
for(int i=4;i<n;i=i+2){l[i]=0;}
for(int i=3;i<n;i=i+2)
	{
	for(int j=i+i;j<n;j=j+i)
		{
		l[j]=0;
		}
	}
for(int i=2;i<n;i++)
	{
	if(l[i]==0){}
	else{cout<<l[i]<<"\n";}
	}

return 0;
}
