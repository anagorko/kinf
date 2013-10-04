#include<iostream>
#include<string>
using namespace std;
int main()
{
int r;
string s;
cout<<"Wybierz szyfr:\n 1. Morse'a\n 2. GA-DE-RY-PO-LU-KI\n 3. PO-LI-TY-KA-RE-NU\n 4. KONIEC\n";
cin>>r;
cin.ignore(1000000, '\n');
if(r==1)//Morse'a
	{
	cout<<"Proszę wpisać tekst.\n Program ten przetwarza tylko alfabet angielski oraz cyfry w pełnym zapisie\n";
	getline(cin, s);
	for(int i=0;i<s.size();i++)
		{
		if(s[i]=='A'||s[i]=='a')cout<<".-/";
		if(s[i]=='B'||s[i]=='b')cout<<"-.../";
		if(s[i]=='C'||s[i]=='c')cout<<"-.-./";
		if(s[i]=='D'||s[i]=='d')cout<<"-../";
		if(s[i]=='E'||s[i]=='e')cout<<"./";
		if(s[i]=='F'||s[i]=='f')cout<<"..-./";
		if(s[i]=='G'||s[i]=='g')cout<<"--./";
		if(s[i]=='H'||s[i]=='h')cout<<"..../";
		if(s[i]=='I'||s[i]=='i')cout<<"../";
		if(s[i]=='J'||s[i]=='j')cout<<".---/";
		if(s[i]=='K'||s[i]=='k')cout<<"-.-/";
		if(s[i]=='L'||s[i]=='l')cout<<".-../";
		if(s[i]=='M'||s[i]=='m')cout<<"--/";
		if(s[i]=='N'||s[i]=='n')cout<<"-./";
		if(s[i]=='O'||s[i]=='o')cout<<"---/";
		if(s[i]=='P'||s[i]=='p')cout<<".--./";
		if(s[i]=='Q'||s[i]=='q')cout<<"--.-/";
		if(s[i]=='R'||s[i]=='r')cout<<".-./";
		if(s[i]=='S'||s[i]=='s')cout<<".../";
		if(s[i]=='T'||s[i]=='t')cout<<"-/";
		if(s[i]=='U'||s[i]=='u')cout<<"..-/";
		if(s[i]=='V'||s[i]=='v')cout<<"...-/";
		if(s[i]=='W'||s[i]=='w')cout<<".--/";
		if(s[i]=='X'||s[i]=='x')cout<<"-..-/";
		if(s[i]=='Y'||s[i]=='y')cout<<"-.--/";
		if(s[i]=='Z'||s[i]=='z')cout<<"--../";
		if(s[i]=='1')cout<<".----/";
		if(s[i]=='2')cout<<"..---/";
		if(s[i]=='3')cout<<"...--/";
		if(s[i]=='4')cout<<"....-/";
		if(s[i]=='5')cout<<"...../";
		if(s[i]=='6')cout<<"-..../";
		if(s[i]=='7')cout<<"--.../";
		if(s[i]=='8')cout<<"---../";
		if(s[i]=='9')cout<<"----./";
		if(s[i]=='0')cout<<"-----/";
		if(s[i]==' ')cout<<"/";
		}
	cout<<"/\n";
	}

if(r==2)//Gaderypoluki
	{
	cout<<"Proszę wpisać tekst.\n";
	getline(cin, s);
	for(int i=0;i<s.size();i++)
		{
		if(s[i]=='A'){s[i]='G';continue;}
		if(s[i]=='a'){s[i]='g';continue;}
		if(s[i]=='D'){s[i]='E';continue;}
		if(s[i]=='d'){s[i]='e';continue;}
		if(s[i]=='E'){s[i]='D';continue;}
		if(s[i]=='e'){s[i]='d';continue;}
		if(s[i]=='G'){s[i]='A';continue;}
		if(s[i]=='g'){s[i]='a';continue;}
		if(s[i]=='I'){s[i]='K';continue;}
		if(s[i]=='i'){s[i]='k';continue;}
		if(s[i]=='K'){s[i]='I';continue;}
		if(s[i]=='k'){s[i]='i';continue;}
		if(s[i]=='L'){s[i]='U';continue;}
		if(s[i]=='l'){s[i]='u';continue;}
		if(s[i]=='O'){s[i]='P';continue;}
		if(s[i]=='o'){s[i]='p';continue;}
		if(s[i]=='P'){s[i]='O';continue;}
		if(s[i]=='p'){s[i]='o';continue;}
		if(s[i]=='R'){s[i]='Y';continue;}
		if(s[i]=='r'){s[i]='y';continue;}
		if(s[i]=='U'){s[i]='L';continue;}
		if(s[i]=='u'){s[i]='l';continue;}
		if(s[i]=='Y'){s[i]='R';continue;}
		if(s[i]=='y'){s[i]='r';continue;}
		}
	cout<<s;
	}

if(r==3)//Politykarenu
	{
	
	}
cout<<"\n";

return 0;
}
