#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main()
{
int n,a,b,w[2],m=0;
for(int i=0;i<2;i++){w[i]=0;}
cin>>n;
vector<int> t;
for(int i=0;i<n*2;i++)
	{
	cin>>a;
	t.push_back(a);
	}
//sortowanie
sort(t.begin(),t.end());
//koniec sortowanie
t.push_back(0);
a=t[0];
b=1;
for(int i=1;i<t.size();i++)
	{
	if(t[i]==a){b++;}
	else
		{
		if(b%2==1)
			{
			w[m]=a;
			m++;
			}
		a=t[i];
		b=1;
		}
	if(m==2){break;}
	}

if(w[0]==w[1]){cout<<"NIE\n";}
if(w[0]<w[1]){cout<<w[0]<<" "<<w[1]<<"\n";}
if(w[0]>w[1]){cout<<w[1]<<" "<<w[0]<<"\n";}

return 0;
}
