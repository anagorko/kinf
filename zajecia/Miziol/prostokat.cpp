#include<iostream>
using namespace std;
int main()
{
int ax,ay,wx1=-1,wx2=-1,wy1=-1,wy2=-1,r,n;
cin>>n;
for(int i=n ;i>0;i--)
	{
	cin>>ax;
	if(ax==wx1)
		{
		ax=wx2;
		}
	if(ax<wx1)
		{
		ax=wx2;
		}
	if(ax>wx1)
		{
		wx1=wx2;
		ax=wx1;
		}
	cin>>ay;
	if(ay==wy1)
		{
		ay=wy2;
		}
	if(ay<wy1)
		{
		ay=wy2;
		}
	if(ay>wy1)
		{
		wy1=wy2;
		ay=wy1;
		}


	}
r=2*(wx1-wx2)+2*(wy1-wy2);
cout<<r<<"\n";
return 0;
}
