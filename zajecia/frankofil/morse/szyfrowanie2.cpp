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
	for (int i = 0; i < dl; i++){
		switch(a[i]){
		case 'a':
			cout<<".-/";break;
		case 'b':
			cout<<"-.../";break;
		case 'c':
			cout<<"-.-./";break;
		case 'd':
			cout<<"-../";break;
		case 'e':
			cout<<"./";break;
		case 'f':
			cout<<"..-./";break;
		case 'g':
			cout<<"--./";break;
		case 'h':
			cout<<"..../";break;
		case 'i':
			cout<<"../";break;
		case 'j':
			cout<<".---/";break;
		case 'k':
			cout<<"-.-/";break;
		case 'l':
			cout<<".-../";break;
		case 'm':
			cout<<"--/";break;
		case 'n':
			cout<<"-./";break;
		case 'o':
			cout<<"---/";break;
		case 'p':
			cout<<".--./";break;
		case 'q':
			cout<<"--.-/";break;
		case 'r':
			cout<<".-./";break;
		case 's':
			cout<<".../";break;
		case 't':
			cout<<"-/";break;
		case 'u':
			cout<<"..-/";break;
		case 'w':
			cout<<".--/";break;
		case 'v':
			cout<<"...-/";break;
		case 'x':
			cout<<"-..-/";break;
		case 'y':
			cout<<"-.--/";break;
		case 'z':
			cout<<"--../";break;
		case '1':
			cout<<".----/";break;
		case '2':
			cout<<"..---/";break;
		case '3':
			cout<<"...--/";break;
		case '4':
			cout<<"....-/";break;
		case '5':
			cout<<"...../";break;
		case '6':
			cout<<"-..../";break;
		case '7':
			cout<<"--.../";break;
		case '8':
			cout<<"---../";break;
		case '9':
			cout<<"----./";break;
		case ' ':
			cout<<"/";break;
		case ',':
			cout<<"/,/";break;
		case '.':
			cout<<"/./";break;
		}
	}
}
