#include<iostream>
using namespace std;
int main()
{
	int n;
	cout<<"\nWitaj! Program ten liczy pola figur";
	while (1) {
	float w;
	cout<<"\n1. Pole kwadratu\n2. Pole kola\n3. Pole trapez\n4. Pole prostokąta\n5. Pole rombu\n6. Pole równoległoboku\n7. Pole trókata\n8. Zakończ\n";
	cin>>n;
	cout<<"\n";
		if (n==1)
	{
	int a;
	cout<<"Podaj dlugosc boku kwadratu\n";
	cin>>a;
	w=a*a;
	cout<<"Pole jest równe "<<w<<" centymetrów kwadratowych\n";
	}
		if (n==2)
	{
	float a;
	cout<<"Podaj dlugosc promienia kola\n";
	cin>>a;
	w=3.14*(a*a);
	cout<<"Pole jest równe "<<w<<"centymetrów kwadratowych\n";
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
	int a,b;
	cout<<"Podaj a\n";
	cin>>a;
	cout<<"Podaj b\n";
	cin>>b;
	cout<<"Pole jest równe "<<a*b<<" centymetrów kwadratowych\n";
	}
		if (n==5)
	{
	int a,h;
	cout<<"Podaj a\n";
	cin>>a;
	cout<<"Podaj h\n";
	cin>>h;
	cout<<"Pole jest równe "<<a*h<<" centymetrów kwadratowych\n";
	}
		if (n==6)
	{
	int a,h;
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
		if (n==8)
	{
	cout<<"Do zobaczenia\n";
	break;
	}
	}
return 0;
}
