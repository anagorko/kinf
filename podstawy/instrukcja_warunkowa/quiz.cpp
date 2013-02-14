#include<iostream>
using namespace std;

int main()
{
	int punkty = 0;

	cout << "\n==================\n";
	cout << "Bardzo Trudny Test\n";
	cout << "==================\n\n";
	cout << "\n";
	cout << "+1 za dobra odpowiedz,\n-1 za zla odpowiedz,\n";
	cout << "0 za brak odpowiedzi (wpisz 0 jesli nie wiesz).\n\n";

	cout << "1. Podaj date bitwy pod Grunwaldem: ";

	int data;

	cin >> data;

	if (data == 1410) {
		punkty = punkty + 1;		
	} else if (data == 0) {

	} else {
		punkty = punkty - 1;
	}

	cout << "\n";
	cout << "2. Ile zer ma kwintylion? ";

	int zera;
	cin >> zera;

	if (zera == 30) {
		punkty = punkty + 1;
	} else if (zera == 0) {
		
	} else {
		punkty = punkty - 1;
	}

	cout << "\n";
	cout << "3. Tetrahedron to: \n";
	cout << "  a) czterochlorek olowiu\n";
	cout << "  b) czworoscian\n";
	cout << "  c) miasto w Galilei\n\n";
	cout << "Wybierz odpowiedz: ";

	string odp;
	cin >> odp;
	if (odp == "b") {
		punkty = punkty + 1;
	} else if (odp == "0") {
		
	} else {
		punkty = punkty - 1;
	}

	cout << "\n\nTwoj wynik: " << punkty << "/3\n\n";

	cout << "Ocena: ";
	switch (punkty) {
		case -3:
		case -2:
		case -1:
		case 0: cout << "1 Ndst. Slabo!!!\n";
			break;
		case 1: cout << "2 dop. Slaba trojka albo mocna dwojka... postawie Ci mocna dwoje.\n";
			break;
		case 2: cout << "3 dst. Od biedy ujdzie..\n";
			break;
		case 3: cout << "Czworka. Na piatke umie tylko nauczyciel. \n";
			break;
		default: cout << "Uzyskales wynik poza skala 8-)\n";
	}

	
	return 0;
}


