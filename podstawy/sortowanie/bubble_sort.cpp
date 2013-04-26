#include<iostream>
using namespace std;

int main()
{
    // odczytanie danych
    
    int ile;
    cin >> ile;
    
    int t[ile];
    for (int i = 0; i < ile; i++) {
        cin >> t[i];
    }
    
    // sortowanie
    
    int ostatnia_zamiana = ile;
    while (ostatnia_zamiana > 0) {
        int tmp = 0;
        for (int i = 0; i < ostatnia_zamiana - 1; i++) {
            if (t[i] > t[i+1]) {
                int a = t[i];
                t[i] = t[i+1];
                t[i+1] = a;
                tmp = i+1;
            }
        }
        ostatnia_zamiana = tmp;
    }
    
    // wypisanie wyniku
    
    for (int i = 0; i < ile; i++) {
        cout << t[i] << " ";
    }
    
    return 0;
}
