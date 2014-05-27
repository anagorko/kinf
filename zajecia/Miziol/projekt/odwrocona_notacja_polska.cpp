#include<iostream>
using namespace std;
int main()
{
//zmienne
struct stos
	{
	float t[1000];
	int i;
	void init()
		{
		i=0;
		}
	bool empty()
		{
		return i==0;
		}
	void insert(int r)
		{
		t[i]=r;
		i++;
		}
	float top()
		{
		return t[i];
		}
	void remove()
		{
		i--;
		}
	};

stos st;
st.init();
string s;
float r=0;
int a,b;
bool z=false;
//zmienne
//wczytywanie i liczenie
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
	if(s[i]==' ')
		{
		if(z=false)
			{
			st.insert(r);
			r=0;
			}
		if(z=true)
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
		r=a+b;
		st.insert(r);
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
	}
//wczytywanie i liczenie

cout<<"Wynik to "<<st.top()<<"\n";

return 0;
}
