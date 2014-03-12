#include<iostream>
using namespace std;
int main()
{
int p,n;
cin>>p;
for(int i=0;i<p;i++)
	{
	cin>>n;
	if(n%3!=0){cout<<"NIE\n";}
	else{cout<<"TAK\n";}
	}
return 0;
}
