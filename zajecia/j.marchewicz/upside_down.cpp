#include<iostream>
using namespace std;
int main()
{
	string s;
	getline(cin,s);
	for (int i=0; i<s.length(); i++)
	{
		switch (s[ s.length()-1-i])
		{
			case 'a': cout<< "ɐ"; break;
			case 'b': cout<< "q"; break;
			case 'c': cout<< "ɔ"; break;
			case 'd': cout<< "p"; break;
			case 'e': cout<< "ǝ"; break;
			case 'f': cout<< "ɟ"; break;
			case 'g': cout<< "ƃ"; break;
			case 'h': cout<< "ɥ"; break;
			case 'i': cout<< "ı"; break;
			case 'j': cout<< "ɾ"; break;
			case 'k': cout<< "ʞ"; break;
			case 'l': cout<< "l"; break;
			case 'm': cout<< "ɯ"; break;
			case 'n': cout<< "u"; break;
			case 'o': cout<< "o"; break;
			case 'p': cout<< "d"; break;
			case 'r': cout<< "ɹ"; break;
			case 's': cout<< "s"; break;
			case 't': cout<< "ʇ"; break;
			case 'u': cout<< "n"; break;
			case 'w': cout<< "m"; break;
			case 'y': cout<< "ʎ"; break;
			case 'z': cout<< "z"; break;
			case ' ': cout<< " "; break;
		}
	}

	cout << endl;
	return 0;
}




