#include <iostream>
#include <string>

using namespace std;
int main()
{
	string a;
	string s;
	for(int i=0; i!=1;)
	{
		cout << "Prawidłowa odpowiedź: "<< endl;
		getline (cin,a);
		cout << "Odpowiedź pytanego: "<< endl;
		getline (cin,s);
		if (s.length() != a.length())
		{
			cout<< "Odpowiedź pytanego jest za krótka o " << int (a.length() - s.length()) << " znaków."<< endl << "Wpisz jeszcze raz" << endl;
		}
		else i++;
	}
		int wynik=0;
		for (int i=0; i < s.length(); i++)
		{
			if(s[i] != a[i]) {wynik++;}
		}

	cout<<"Liczba błędów: "<<wynik<< endl;

}
