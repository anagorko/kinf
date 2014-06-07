#include<iostream>
using namespace std;
void pola()
{
int n;
const float PI=3.14;
float a,b,h,r,w;
powitanie();
ktora();
cin>>n;
cout<<"\n";
if (n==1)
	{
	cout<<"Podaj a ";
	cin>>a;
	w=a*a;
	cout<<"Pole kwadratu o boku "<<a<<" jest równe "<<w<<" centymetrów kwadratowych\n"<<a<<"*"<<a<<"="<<w<<"\n";
	}
if (n==2)
	{
	cout<<"Podaj a\n";
	cin>>a;
	cout<<"Podaj b\n";
	cin>>b;
	cout<<"Pole prostokąta o bokach a="<<a<<"; b="<<b<<" jest równe "<<w<<" centymetrów kwadratowych\n"<<a<<"*"<<b<<"="<<w<<"\n";
	}
if (n==3)
	{
	cout<<"Podaj a\n";
	cin>>a;
	cout<<"Podaj h\n";
	cin>>h;
	cout<<"Pole trójkąta o podstawie a="<<a<<" i wysokości h="<<h<<" jest równe "<<w<<" centymetrów kwadratowych\n"<<"("<<a<<"*"<<h<<")/2="<<w<<"\n";
	}
if (n==4)
	{
	cout<<"Podaj a ";
	cin>>a;
	cout<<"\nPodaj b ";
	cin>>b;
	cout<<"\nPodaj h ";
	cin>>h;
	w=((a+b)*h)/2.0;
	cout<<"Pole trapezu o podstawach a="<<a<<"; b="<<b<<" i wysokości h="<<h<<" jest równe "<<w<<" centymetrów kwadratowych\n"<<"(("<<a<<"+"<<b<<")*"<<h<<"/2="<<w<<"\n";
	}
if (n==5)
	{
	cout<<"Podaj a\n";
	cin>>a;
	cout<<"Podaj h\n";
	cin>>h;
	cout<<"Pole równoległoboku o podstawie a="<<a<<" i wysokości h="<<h<<" jest równe "<<w<<" centymetrów kwadratowych\n"<<a<<"*"<<h<<"="<<w<<"\n";
	}
if (n==6)
	{
	cout<<"Podaj r ";
	cin>>a;
	w=PI*(a*a);
	cout<<"Pole koła o promieniu "<<a<<" jest równe "<<w<<" centymetrów kwadratowych\n"<<"("<<r<<"*"<<r<<")*PI="<<w<<"\n";
	}
return;
}
