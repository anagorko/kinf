#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
long long int a=0,b=0,d=0,s=0,w=0,wi=0,w2=0;
int n=0;
cin>>a;
cin>>b;
cin>>n;
for(int i=0;i<n;i++)
	{
	w2=0;
	scanf("%lld %lld %lld", &d, &s, &w);
	if(a>=d)
		{
		if(b>=s||b>=w){printf("TAK\n");w2=1;}
		}
	if(a>=s&&w2==0)
		{
		if(b>=d||b>=w){printf("TAK\n");w2=1;}
		}
	if(a>=w&&w2==0)
		{
		if(b>=d||b>=s){printf("TAK\n");w2=1;}
		}
	if(b>=d&&w2==0)
		{
		if(a>=s||a>=w){printf("TAK\n");w2=1;}
		}
	if(b>=s&&w2==0)
		{
		if(a>=d||a>=w){printf("TAK\n");w2=1;}
		}
	if(b>=w&&w2==0)
		{
		if(a>=d||a>=s){printf("TAK\n");w2=1;}
		}
	if(w2==0){printf("NIE\n");wi++;}
	}
cout<<wi<<"\n";
return 0;
}
