#include<iostream>
using namespace std;
int main()
{
int d,x,y,xr,yr,dw=0,r,w;
cin>>d;
cin>>r;
cin>>xr;
cin>>yr;
while(d-->0)
	{
	cin>>x;
	cin>>y;
	x=x-xr;
	y=y-yr;
		if(x==xr,y==yr)
			{}
		if(r*r>=x*x+y*y)
			{}
		if(r*r<x*x+y*y)
			{
			dw++;
			}
	}
cout<<dw;
return 0;
}
