#include<iostream>
using namespace std;

void ulamki()
{
cout<<"Witaj w kalkulatorze który operuje na ułamkach zwykłych.\nPodaj swoje działanie\n";
//zmienne
int a[2],b[2],w[2];
int wa[2],wb[2];
//zerowanie
for(int i=0;i<2;i++)
	{
	a[i]=0;
	b[i]=0;
	w[i]=0;
	}
//zerowanie
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
		l++;
		}
	if(s[i]=='-')
		{
		z='-';
		l++;
		}
	if(s[i]=='*')
		{
		z='*';
		l++;
		}
	if(s[i]=='/')
		{
		z='/';
		l++;
		}
	}
//koniec wczytywania

for(int i=0;i<2;i++)
	{
	wa[i]=a[i];
	wb[i]=b[i];
	}

//obliczenia
if(z=='+')
	{
	if(a[1]==b[1])
		{
		w[1]=a[0];
		}
	else
		{
		a[0]=a[0]*b[1];
		b[0]=b[0]*a[1];
		w[1]=a[1]*b[1];
		}
	w[0]=a[0]+b[0];
	}
if(z=='-')
	{
	if(a[1]==b[1])
		{
		w[1]=a[0];
		}
	else
		{
		a[0]=a[0]*b[1];
		b[0]=b[0]*a[1];
		w[1]=a[1]*b[1];
		}
	w[0]=a[0]+b[0];
	}
if(z=='*')
	{
	w[0]=a[0]*b[0];
	w[1]=a[1]*b[1];
	}
if(z=='/')
	{
	w[0]=a[0]*b[1];
	w[1]=a[1]*b[0];
	}
//koniec obliczenia
//poczatek skracanie

//koniec skracanie
//wypisywanie wyniku
cout<<"Wynikiem działania "<<wa[0]<<"|"<<wa[1]<<z<<wb[0]<<"|"<<wb[1]<<" jest "<<w[0]<<"|"<<w[1]<<"\n";
cout<<wa[0]<<"|"<<wa[1]<<z<<wb[0]<<"|"<<wb[1]<<"="<<w[0]<<"|"<<w[1]<<"\n";

return;
}
