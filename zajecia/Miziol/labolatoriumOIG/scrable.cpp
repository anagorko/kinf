#include<iostream>
using namespace std;
int main()
{
int a,m=0,b;
string s;
cin>>s;
//getline(cin,s);
char w[s.length()];
for(int i=0;i<s.length();i++)
	{
	w[i]=';';
	}
a=0;
b=s.length()-1;
for(int i=0;i<s.length()/2;i++)
	{
	w[m]=s[a];
	m++;
	w[m]=s[b];
	m++;
	b--;
	a++;
	}
if(s.length()%2==1)
	{
	w[s.length()-1]=s[a];
	}
for(int i=0;i<s.length();i++)
	{
	cout<<w[i];
	}
cout<<"\n";

return 0;
}
