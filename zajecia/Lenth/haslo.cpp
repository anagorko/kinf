#include<iostream>
using namespace std;
int main()
{
	string haslo;
	string pass = "mellon";
	cin >> haslo;
	if(haslo==pass)
	{
		cout << "Haslo poprawne!\n";
	}
	else
	{
		cout << "Haslo bledne!\n";
	}
	return 0;
}
