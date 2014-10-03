#include<iostream>
using namespace std;


int main()
{
	string s;
	cin >> s;
	cout << "Pierwsza litera: " << s[0] << ". Dlugosc " << s.length() << "\n";
	char ostatnia_litera = s[s.length() - 1];
	cout << "Ostatnia litera: " << ostatnia_litera << "\n";
	switch(ostatnia_litera)
	{
	case 'a':
		cout << "Kobieta\n";
		break; 

	default:
		cout << "Mezczyzna\n";	
	}
	return 0;	
}

