#include<iostream>
using namespace std;
int main()
{
int p,k,pw,r;
cin>>p>>k;
int w[p];
pw=p-1;
r=k;
for(int i=0;i<p;i++)
	{
	r=r/5;
	w[pw]=k-(5*r);
	pw--;
	r=(r-1)/2;
	k=r;
	}
cout<<r<<"\n";
for(int i=0;i<p;i++)
	{
	cout<<w[i]<<"\n";
	}

return 0;
}
