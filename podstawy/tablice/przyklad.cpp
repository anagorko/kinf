#include <iostream>
using namespace std;

int main()
{
	double odleglosc[] = {44.14, 720.52, 96.08, 468.78, 6.28};

	cout << "Druga odleglosc = " << odleglosc[1] << endl;
	cout << "Piata odleglosc = " << odleglosc[4] << endl;

	// w tym miejscu dopisz kod
	
        cout << "Wszystkie odleglosci: " << endl;
        for (int i = 0; i < 5; i++) {
            cout << "Odleglosc nr " << i << " " << odleglosc[i] << endl;
        }

        cout << "Najwieksza odleglosc: ";
        double n = 0;
        for (int i = 0; i < 5; i++) {
            if (odleglosc[i] > n) { n = odleglosc[i]; }
        }
        cout << n << endl;

	return 0;
}