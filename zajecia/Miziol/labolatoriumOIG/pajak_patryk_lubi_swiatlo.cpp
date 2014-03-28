#include<iostream>
using namespace std;
int main()
{
int a,b,d,z,w=0;
cin>>z>>d;
int t[d];
for(int i=0;i<d;i++){t[i]=0;}
for(int i=0;i<z;i++)
	{
	cin>>a>>b;
	a--;
	b--;
	if(a==b){t[a]++;}
	if(b>a)
		{
		for(int i=a;i<b;i++)
			{
			t[i]++;
			}
		}
	if(a>b)
		{
		for(int i=b;i<a;i++)
			{
			t[i]++;
			}
		}
	}
for(int i=0;i<d;i++)
	{
	if(t[i]>t[w])
		{
		w=i;
		}
	}
w++;
cout<<w<<"\n";

return 0;	
}
