#include<iostream>
#include<string.h>
using namespace std;
int main()
{
int a,aw=0,bw=1,b;
string s;
getline(cin,s);
char w[s.length()];
a=0;
b=s.length();
for(int i=0;i<s.length()/2;i++)
	{
	w[aw]=s[a];
	w[bw]=s[b];
	bw=bw+2;
	b--;
	aw=aw+2;
	a++;
	for(int i=0;i<s.length()+1;i++)
		{
		cout<<w[i];
		}
	cout<<"\n";
	}
if(s.length()%2==1)
	{
	w[s.length()]=s[(s.length())/2+1];
	}
for(int i=0;i<s.length()+1;i++)
	{
	cout<<w[i];
	}
cout<<"\n";

return 0;
}
