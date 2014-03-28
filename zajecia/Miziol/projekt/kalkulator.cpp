#include<iostream>
#include<string.h>
using namespace std;
int main()
{
cout<<"Podaj swoje działanie\n";
//zmienne
float a=0,b=0,w=0;
string s;
bool t=true;
char z;
//głowna część programu
getline (cin,s);

for(int i=0;i<s.size();i++)
	{
	if(s[i]=='0')
		{
		if(t==true){a=a*10+0;}
		if(t==false){b=b*10+0;}
		}
	if(s[i]=='1')
		{
		if(t==true){a=a*10+1;}
		if(t==false){b=b*10+1;}
		}
	if(s[i]=='2')
		{
		if(t==true){a=a*10+2;}
		if(t==false){b=b*10+2;}
		}
	if(s[i]=='3')
		{
		if(t==true){a=a*10+3;}
		if(t==false){b=b*10+3;}
		}
	if(s[i]=='4')
		{
		if(t==true){a=a*10+4;}
		if(t==false){b=b*10+4;}
		}
	if(s[i]=='5')
		{
		if(t==true){a=a*10+5;}
		if(t==false){b=b*10+5;}
		}
	if(s[i]=='6')
		{
		if(t==true){a=a*10+6;}
		if(t==false){b=b*10+6;}
		}
	if(s[i]=='7')
		{
		if(t==true){a=a*10+7;}
		if(t==false){b=b*10+7;}
		}
	if(s[i]=='8')
		{
		if(t==true){a=a*10+8;}
		if(t==false){b=b*10+8;}
		}
	if(s[i]=='9')
		{
		if(t==true){a=a*10+9;}
		if(t==false){b=b*10+9;}
		}
	if(s[i]=='+')
		{
		z='+';
		t=false;
		}
	if(s[i]=='-')
		{
		z='-';
		t=false;
		}
	if(s[i]=='*')
		{
		z='*';
		t=false;
		}
	if(s[i]=='/')
		{
		z='/';
		t=false;
		}
	/*if(s[i]=='^')
		{
		z='^';
		t=false;
		}*/
	}
//obliczenia
if(z=='+')
	{
	w=a+b;
	}
if(z=='-')
	{
	w=a-b;
	}
if(z=='*')
	{
	w=a*b;
	}
if(z=='/')
	{
	w=a/b;
	}
//wypisywanie wyniku
cout<<"="<<w<<"\n";

return 0;
}
