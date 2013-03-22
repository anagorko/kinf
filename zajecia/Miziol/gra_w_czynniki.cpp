#include<iostream>
using namespace std;
int main()
{
//sito
int n=50000,w=0;
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
	else{w++;}
	}
//koniec sito
//lpierwsze
int lp[w],ilp;
for(int i=0;ilp<w;i++)
	{
	if(l[i]!=0)
		{
		lp[i]=l[i];
		ilp++;
		}
	}
//koniec lpierwsze
//zmienna kto wygra
ilp=0;
bool wy[100000];
for(int i=1;i<100000;i++)
	{
	if(i=1){wy[i]=false;}
	if(i=lp[ilp]){ilp++;wy[i]=false;}
	}
//koniec kto wygra
//przykłady
int p,r;
cin>>p;
for(int i=0;i<p;i++)
	{
	cin>>r;
	if(wy[r]==true){cout<<"magda\n";}
	else{cout<<"bartek\n";}
	}

return 0;
}
