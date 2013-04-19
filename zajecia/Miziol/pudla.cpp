#include<iostream>
using namespace std;
int main()
{
int p[100000];
int naj=0,i,ob;
//zerowanie
for (int z=0;z<100000;z++){p[z]=0;}
//program właściwy
cin>>i;
for (int j=0;j<i;j++)
	{
	cin>>ob;
	
	p[ob]=p[ob]+ob;
	}
naj=1;
for (int m=0;m<100000;m++)
	{
	if (p[m]<=naj){}
	if (p[m]>naj){naj=p[m];}
	}
cout<<naj<<"\n";

return 0;
}
