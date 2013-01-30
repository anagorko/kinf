#include<fstream>
using namespace std;

int main()
{
    fstream plik;
    plik.open ("czcionka.psf", ios::in | ios::out | ios::binary);
    
    char t[2000];
    plik.read(t, 2000);
    
    // tu wpisujemy nasze instrukcje
    
    int n = 1499;
    
    for (int i = 0; i < 13; i++) {
        t[n+i] = t[n+1] | (t[n+i] >> 1);
    }
    
    // tu plik jest zapisywany z powrotem
    
    plik.seekp(0);
    plik.write(t, 2000);
    
    plik.close();
    return 0;
}
