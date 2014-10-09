#include <iostream>
using namespace std;

int main()
{
	char tx[64], sz[64];
	int i=0, p, s;
	cout << "Tekst do szyfrowania: \n", cin >> tx;
	cout << "Klucz: \n", cin >> s;		
	p = 'z' - 'a' + 1;
	while(tx[i]) sz[i] = (tx[i] - 'a' + s)%p + 'a', ++i; sz[i]='\0';
	cout << "Zaszyfrowany tekst: " << sz << "\n";
	return 0;
}
