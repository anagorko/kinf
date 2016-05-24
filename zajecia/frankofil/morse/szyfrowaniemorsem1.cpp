#include<iostream>
#include<string>

using namespace std;

int main() 
{
	string a;

	cout<<"Podaj tekst do zaszyfrowania."<<endl; 
	getline(cin,a);
	
	cout<<"Zaszyfrowany tekst:"<<endl;
	int dl;
	dl = a.length();
	for (int i = 0; i < a.length() ; i++){
		if(a[i]=='a')
			cout<<".-/";
		if(a[i]=='b')
			cout<<"-.../";
		if(a[i]=='c')
			cout<<"-.-./";
		if(a[i]=='d')
			cout<<"-../";
		if(a[i]=='e')
			cout<<"./";
		if(a[i]=='f')
			cout<<"..-./";
		if(a[i]=='g')
			cout<<"--./";
		if(a[i]=='h')
			cout<<"..../";
		if(a[i]=='i')
			cout<<"../";
		if(a[i]=='j')
			cout<<".---/";
		if(a[i]=='k')
			cout<<"-.-/";
		if(a[i]=='l')
			cout<<".-../";
		if(a[i]=='m')
			cout<<"--/";
		if(a[i]=='n')
			cout<<"-./";
		if(a[i]=='o')
			cout<<"---/";
		if(a[i]=='p')
			cout<<".--./";
		if(a[i]=='q')
			cout<<"--.-/";
		if(a[i]=='r')
			cout<<".-./";
		if(a[i]=='s')
			cout<<".../";
		if(a[i]=='t')
			cout<<"-/";
		if(a[i]=='u')
			cout<<"..-/";
		if(a[i]=='w')
			cout<<".--/";
		if(a[i]=='v')
			cout<<"...-/";
		if(a[i]=='x')
			cout<<"-..-/";
		if(a[i]=='y')
			cout<<"-.--/";
		if(a[i]=='z')
			cout<<"--../";
		if(a[i]=='1')
			cout<<".----/";
		if(a[i]=='2')
			cout<<"..---/";
		if(a[i]=='3')
			cout<<"...--/";
		if(a[i]=='4')
			cout<<"....-/";
		if(a[i]=='5')
			cout<<"...../";
		if(a[i]=='6')
			cout<<"-..../";
		if(a[i]=='7')
			cout<<"--.../";
		if(a[i]=='8')
			cout<<"---../";
		if(a[i]=='9')
			cout<<"----./";
		if(a[i]==' ')
			cout<<"/";
		if(a[i]==',')
			cout<<"/,/";
		if(a[i]=='.')
			cout<<"/./";
	}
}
