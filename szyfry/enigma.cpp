#include<iostream>
#include<string>
#include<math.h>

using namespace std;

string kryptogram = 
	"hyxvkazrnxnoffyxneffufkrmfyxnerztqunrjtrjotkaisufuxvufhyxw" 
	"ulrzxvywvfxwiofkxhzhsthrbomthqsihkxhjufzgkzhsebkntcwmlktkv" 
	"gxessthrjotatraafphrktvfnwgnrvbkntvlghxerrghzwsemcyilntwzh" 
	"ijgszjcrfhgccjmeanxllxryqfghkmbvwxudsrmlotkrlmzhsnkizcvvww"  
	"krjrgxufhyxejmwebwzrokbstotkaijiodhrjdwjmvochpxwoazfgichcj" 
	"bkttvzlaotvdrxxusetqkofkxkg";

const int d = 6; // dlugosc hasla

int l = 0; // numer aktualnie analizowanej litery hasła

char c; // sprawdzana litera do klucza

int freq[26]; // to będziemy liczyć: częstotliwość występowania liter

float odch[26]; // to będziemy liczyć odchylenia standardowe z populacji
                // dla wszystkich możliwych podstawień c

char najlepsza_litera[d]; // znalezione litery z najmniejszymi odchyleniami

float letter_freq[26] = {
	8.167,  // a
	1.492,  // b
	2.782,  // c
	4.253,  // d
	12.702, // e
	2.228,  // f
	2.015,  // g
	6.094,  // h
	6.966,  // i
	0.153,  // j
	0.772,  // k
	4.025,  // l 
	2.406,  // m
	6.749,  // n
	7.507,  // o
	1.929,  // p
	0.095,  // q
	5.987,  // r
	6.327,  // s
	9.056,  // t
	2.758,  // u
	0.978,  // v
	2.360,  // w
	0.150,  // x
	1.974,  // y
	0.074   // z
};

int main()
{
	// ustalamy wartość l (przebiega liczby od 0 do d-1)
	for (l = 0; l < d; l++) {

		// ustalamy wartość c (przebiega litery od 'a' do 'z')
		// jest to testowana właśnie litera do hasła
		for (c = 'a'; c <= 'z'; c++) {

			// dla ustalonego l i c obliczamy częstotliwość występowania
			// liter w ciągu (bierzemy co l-tą literę, przesuwamy o c w lewo
			// i zliczamy wystąpienia)

			for (int i = 0; i < 26; i++) {
				freq[i] = 0;
			}
			for (int i = l; i < kryptogram.length(); i += d) {
				// bierzemy litery kryptogramu co d, zaczynamy od l-tej
				char k = kryptogram[i];

				k = k - c;
				if (k < 0) { k = k + 26; }
				freq[k]++;
			}

			// liczymy odchylenie standardowe z populacji :)
			// (wypełniamy jedno miejsce tabeli odch)

			int t = 0;
			for (int i = 0; i < 26; i++) {
				t = t + freq[i];
			}

			float od = 0;
			for (int i = 0; i < 26; i++) {
				float  f = 100.0 * (float) freq[i] / (float) t;

				od = od + (f - letter_freq[i]) * (f - letter_freq[i]);
			}
			od = sqrt(od/ (float) t);

//			cout << "Odchylenie dla litery " << c << " to " << freq[c - 'a'] << " " << od << "\n";

			odch[c - 'a'] = od;
		}

		// szukamy litery z najmniejszym odchyleniem

		float min = 100000000;
		int i_min = -1;

		for (int i = 0; i < 26; i++) {
			if (odch[i] < min) {
				i_min = i; min = odch[i];
			}
		}

		// wypisujemy tę literę

		cout << "Litera nr " << l << " hasła to: " << (char) (i_min + 'a') << "\n";
	}

	return 0;
}
