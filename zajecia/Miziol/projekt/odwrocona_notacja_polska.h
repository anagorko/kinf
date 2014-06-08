#include<iostream>
using namespace std;
void odwrotna_notacja_polska()
{
//zmienne
struct stos
	{
	float t[1000];
	int p;
	void init()
		{
		p=0;
		}
	bool empty()
		{
		return p==0;
		}
	void insert(float r)
		{
		t[p]=r;
		p++;
		}
	float top()
		{
		return t[p-1];
		}
	void remove()
		{
		p--;
		}
	};

stos st;
st.init();
int l;
string s,s2;
float r=0,r2=0;
float a,b;
bool z=false;
//zmienne
//wczytywanie i liczenie
powitanie();
cin.ignore(1,'\n');
getline (cin,s);

for(int i=0;i<s.size();i++)
	{
	if(s[i]=='0')
		{
		r=r*10+0;
		z=false;
		}
	if(s[i]=='1')
		{
		r=r*10+1;
		z=false;
		}
	if(s[i]=='2')
		{
		r=r*10+2;
		z=false;
		}
	if(s[i]=='3')
		{
		r=r*10+3;
		z=false;
		}
	if(s[i]=='4')
		{
		r=r*10+4;
		z=false;
		}
	if(s[i]=='5')
		{
		r=r*10+5;
		z=false;
		}
	if(s[i]=='6')
		{
		r=r*10+6;
		z=false;
		}
	if(s[i]=='7')
		{
		r=r*10+7;
		z=false;
		}
	if(s[i]=='8')
		{
		r=r*10+8;
		z=false;
		}
	if(s[i]=='9')
		{
		r=r*10+9;
		z=false;
		}
	if(s[i]=='.'||s[i]==',')
		{
		i++;
		r2=0;
		for( ; ; )
			{
			if(s[i]=='0')
				{
				r2=r2*10+0;
				}
			if(s[i]=='1')
				{
				r2=r2*10+1;
				}
			if(s[i]=='2')
				{
				r2=r2*10+2;
				}
			if(s[i]=='3')
				{
				r2=r2*10+3;
				}
			if(s[i]=='4')
				{
				r2=r2*10+4;
				}
			if(s[i]=='5')
				{
				r2=r2*10+5;
				}
			if(s[i]=='6')
				{
				r2=r2*10+6;
				}
			if(s[i]=='7')
				{
				r2=r2*10+7;
				}
			if(s[i]=='8')
				{
				r2=r2*10+8;
				}
			if(s[i]=='9')
				{
				r2=r2*10+9;
				}
			if(s[i]!='0'||s[i]!='1'||s[i]!='2'||s[i]!='3'||s[i]!='4'||s[i]!='5'||s[i]!='6'||s[i]!='7'||s[i]!='8'||s[i]!='9')
				{
				break;
				}
			i++;
			}
		s2=r2;
		l=s2.size();
		r2=r2/(10.00*l);
		r=r+r2;
		i++;
		}



//element liczący
	if(s[i]==' ')
		{
		if(z==false)
			{
			st.insert(r);
			r=0;
			}
		if(z==true)
			{
			r=0;
			}
		}
	if(s[i]=='+')
		{
		a=st.top();
		st.remove();
		b=st.top();
		st.remove();
		st.insert(a+b);
		r=0;
		z=true;
		}
	if(s[i]=='-')
		{
		a=st.top();
		st.remove();
		b=st.top();
		st.remove();
		st.insert(a-b);
		r=0;
		z=true;
		}
	if(s[i]=='*')
		{
		a=st.top();
		st.remove();
		b=st.top();
		st.remove();
		st.insert(a*b);
		r=0;
		z=true;
		}
	if(s[i]=='/')
		{
		a=st.top();
		st.remove();
		b=st.top();
		st.remove();
		st.insert(a/b);
		r=0;
		z=true;
		}
//element liczący
	}
//wczytywanie i liczenie

wynik(s,st.top());

return;
}
