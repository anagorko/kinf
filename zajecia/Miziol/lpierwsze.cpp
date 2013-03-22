#include<iostream>
using namespace std;
int main()
{
int n,d;
cin>>n;
for(int i=2;i<n;i++)
	{
	d=2;
	while(d*d<=i)
		{
		if(i%d==0){break;}
		d++;
		}
	if(d*d<=i){;}
	else{cout<<i<<"\n";}
	}
return 0;
}
