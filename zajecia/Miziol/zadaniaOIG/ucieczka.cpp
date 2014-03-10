#include<iostream>
using namespace std;
int main()
{
int a,b,n/*ilość ochroniarzy*/,t/*czas potrzebny*/,d/*czas do końca*/,m/*możliwość początku*/,p=0/*max k bezpieczeństwo*/,r;
bool r2;
cin>>n>>t>>d;
int ch[d];
for(int i=0;i<d;i++)
	{
	ch[i]=0;
	}
for(int i=0;i<n;i++)
	{
	cin>>a>>b;
	a--;
	b--;
	if(a==b){ch[a]++;}
	else
		{
		for(int j=a;j<=b;j++)
			{
			ch[j]++;
			}
		}
	}

m=d-(t-1);
cout<<"0 "<<m<<"\n";

for(int i=0;i<m;i++)
	{
	if(ch[i]>p){p=ch[i];}
	}
int c[p],w[p];
for(int i=0;i<p;i++)
	{
	c[i]=t*-1+1;
	w[i]=0;
	}
r=0;

//góra jest zdrowa 

for(int i=0;i<d;i++)
	{
	if(ch[i]<r)
		{
		for(int j=ch[i];j<r-ch[i];j++)
			{
			if(c[j]>0){w[j]=w[j]+c[j];}
			c[j]=t*-1+1;
			}
		if(ch[i]>0)
			{
				for(int j=ch[i];j>-1;j--)
				{
				c[j]++;
				}
			}
		}
	if(ch[i]>=r)
		{
		for(int j=ch[i]-1;j>-1;j--)
			{
			c[j]++;
			}
		}
	r=ch[i];
	}
for(int i=0;i<p;i++)
	{
	if(c[i]>0){w[i]=w[i]+c[i];}
	}
for(int i=0;i<p;i++)
	{
	if(w[i]>0){cout<<i+1<<" "<<w[i]<<"\n";}
	else{break;}
	}
return 0;
}
