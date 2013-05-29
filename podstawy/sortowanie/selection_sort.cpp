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
    
    for (int i = 0; i < ile; i++) {
        int min_gdzie = i;
        
        for (int j = i + 1; j < ile; j++) {
            if (t[j] < t[min_gdzie]) {
                min_gdzie = j;
            }
        }
        
        int x = t[i];
        t[i] = t[min_gdzie];
        t[min_gdzie] = x;
    }
        
    // wypisanie wyniku
    
    for (int i = 0; i < ile; i++) {
        cout << t[i] << " ";
    }
    
    return 0;
}
