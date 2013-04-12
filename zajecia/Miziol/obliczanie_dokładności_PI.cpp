#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
long long int n;
int z=1,m=1;
double s=0;
cout<<"Ile wyrazów sumować ";
cin>>n;
cout<<"4*(";
for(int i=0;i<n;i++)
{
	s=s+(double)z*1/m;
	z=z*(-1);
	m=m+2;
}
cout<<")="<<fixed<<setprecision(10)<<4*s<<"\n\n\n\n"<<fixed<<setprecision(10)<<4*s<<"\n";

return 0;
}
