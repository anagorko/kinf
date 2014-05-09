#include<iostream>
using namespace std;
void pola()
{
int n;
cout<<"Witaj w liczeniu pól figur\nWybierz pole które chcesz policzyć\n";
float w;
cout<<"1. Pole kwadratu\n2. Pole koła\n3. Pole trapez\n4. Pole prostokąta\n5. Pole rombu\n6. Pole równoległoboku\n7. Pole trókata\n";
cin>>n;
cout<<"\n";
if (n==1)
	{
	float a;
	cout<<"Podaj a ";
	cin>>a;
	w=a*a;
	cout<<"Pole jest równe "<<w<<" centymetrów kwadratowych\n";
	}
if (n==2)
	{
	float a;
	cout<<"Podaj r ";
	cin>>a;
	w=3.14*(a*a);
	cout<<"Pole jest równe "<<w<<" centymetrów kwadratowych\n";
	}
if (n==3)
	{
	float a,b,h;
	cout<<"Podaj a ";
	cin>>a;
	cout<<"\nPodaj b ";
	cin>>b;
	cout<<"\nPodaj h ";
	cin>>h;
	w=((a+b)*h)/2.0;
	cout<<"Pole jest równe "<<w<<" centymetrów kwadratowych\n";
	}
if (n==4)
	{
	float a,b;
	cout<<"Podaj a\n";
	cin>>a;
	cout<<"Podaj b\n";
	cin>>b;
	cout<<"Pole jest równe "<<a*b<<" centymetrów kwadratowych\n";
	}
if (n==5)
	{
	float a,h;
	cout<<"Podaj a\n";
	cin>>a;
	cout<<"Podaj h\n";
	cin>>h;
	cout<<"Pole jest równe "<<a*h<<" centymetrów kwadratowych\n";
	}
if (n==6)
	{
	float a,h;
	cout<<"Podaj a\n";
	cin>>a;
	cout<<"Podaj h\n";
	cin>>h;
	w=a*h;
	cout<<"Pole równe jest "<<w<<" centymetrów kwadratowych\n";
	}
if (n==7)
	{
	float a,h;
	cout<<"Podaj a\n";
	cin>>a;
	cout<<"Podaj h\n";
	cin>>h;
	cout<<"Pole jest równe "<<(a*h)/2<<" centymetrów kwadratowych\n";
	}
return;
}
