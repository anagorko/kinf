#include <iostream>
#include <math.h>
using namespace std;
int main()
{
int n,k,xr,yr,xn,yn,l,d,i;

cin>>n;
cin>>k;
cin>>xr;
cin>>yr;
l=0;

for(i=0;i<n;i=i+1)
{
	cin>>xn;
	cin>>yn;	
	d=sqrt((yn-yr)*(yn-yr)+(xn-xr)*(xn-xr));
	if(d>k)
	{
		l=l++;
	}

}

cout<<l<<"\n";

 return 0;
}
