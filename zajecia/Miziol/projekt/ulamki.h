#include<iostream>
using namespace std;

void ulamki()
{
cout<<"Witaj w kalkulatorze klasycznym.\nPodaj swoje działanie\n";
//zmienne
int a[2],b[2],w[2];
string s;
int l=0;
char z;
//głowna część programu
cin.ignore(1,'\n');
getline (cin,s);
//wczytywanie
for(int i=0;i<s.size();i++)
	{
	if(s[i]=='0')
		{
		if(l==0){a[0]=a[0]*10+0;}
		if(l==1){a[1]=a[1]*10+0;}
		if(l==2){b[0]=b[0]*10+0;}
		if(l==3){b[1]=b[1]*10+0;}
		}
	if(s[i]=='1')
		{
		if(l==0){a[0]=a[0]*10+1;}
		if(l==1){a[1]=a[1]*10+1;}
		if(l==2){b[0]=b[0]*10+1;}
		if(l==3){b[1]=b[1]*10+1;}
		}
	if(s[i]=='2')
		{
		if(l==0){a[0]=a[0]*10+2;}
		if(l==1){a[1]=a[1]*10+2;}
		if(l==2){b[0]=b[0]*10+2;}
		if(l==3){b[1]=b[1]*10+2;}
		}
	if(s[i]=='3')
		{
		if(l==0){a[0]=a[0]*10+3;}
		if(l==1){a[1]=a[1]*10+3;}
		if(l==2){b[0]=b[0]*10+3;}
		if(l==3){b[1]=b[1]*10+3;}
		}
	if(s[i]=='4')
		{
		if(l==0){a[0]=a[0]*10+4;}
		if(l==1){a[1]=a[1]*10+4;}
		if(l==2){b[0]=b[0]*10+4;}
		if(l==3){b[1]=b[1]*10+4;}
		}
	if(s[i]=='5')
		{
		if(l==0){a[0]=a[0]*10+5;}
		if(l==1){a[1]=a[1]*10+5;}
		if(l==2){b[0]=b[0]*10+5;}
		if(l==3){b[1]=b[1]*10+5;}
		}
	if(s[i]=='6')
		{
		if(l==0){a[0]=a[0]*10+6;}
		if(l==1){a[1]=a[1]*10+6;}
		if(l==2){b[0]=b[0]*10+6;}
		if(l==3){b[1]=b[1]*10+6;}
		}
	if(s[i]=='7')
		{
		if(l==0){a[0]=a[0]*10+7;}
		if(l==1){a[1]=a[1]*10+7;}
		if(l==2){b[0]=b[0]*10+7;}
		if(l==3){b[1]=b[1]*10+7;}
		}
	if(s[i]=='8')
		{
		if(l==0){a[0]=a[0]*10+8;}
		if(l==1){a[1]=a[1]*10+8;}
		if(l==2){b[0]=b[0]*10+8;}
		if(l==3){b[1]=b[1]*10+8;}
		}
	if(s[i]=='9')
		{
		if(l==0){a[0]=a[0]*10+9;}
		if(l==1){a[1]=a[1]*10+9;}
		if(l==2){b[0]=b[0]*10+9;}
		if(l==3){b[1]=b[1]*10+9;}
		}
	if(s[i]=='|')
		{
		l++;
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
	if(s[i]=='^')
		{
		z='^';
		t=false;
		}
	if(s[i]=='v')
		{
		z='v';
		t=false;
		}
	if(s[i]=='!')
		{
		z='!';
		t=false;
		}

	}
//koniec wczytywania
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
if(z=='^')
	{
	w=pow(a,b);
	}
if(z=='v'&&a==0)
	{
	w=sqrt(b);
	}
if(z=='v'&&a!=0)
	{
	w=pow(b,(1/a));
	}
if(z=='!'&&a>=1)
	{
	w=1;
	for(int i=1;i<=a;i++)
		{
		w=w*i;
		}
	}

//wypisywanie wyniku
cout<<"Wynikiem działania "<<a<<z<<b<<" jest "<<w<<"\n";
cout<<a<<z<<b<<"="<<w<<"\n";

return;
}
