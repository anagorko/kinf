#include<iostream>
using namespace std;

int S (int &i,int &r,int &n,int &m,int &im, string &s)
{
m=1;
i++;
if(i<n&&s[i]='1'||s[i]='2'||s[i]='3'||s[i]='3'||s[i]='4'||s[i]='5'||s[i]='6'||s[i]='7'||s[i]='8'||s[i]='9')
	{
	S(i,r,s,n,m,im);
	i--;
	}
else
	{
	r=r+(s[i]*m);
	m=m*10;
	
	}
if(im<i){im=i;}
return i,r,s,n,m,im;
}

int main()
{
int n=0,w=0,r,m=1,im;
string s;
cin>>n;
getline(cin,s);
for(int i=0;i<n;i++)
	{
	if(s[i]='1'||s[i]='2'||s[i]='3'||s[i]='3'||s[i]='4'||s[i]='5'||s[i]='6'||s[i]='7'||s[i]='8'||s[i]='9')
		{
		w=w+S(i,r,s,n,m,im);
		}
	r=0;
	im=i;
	}

return 0;
}
