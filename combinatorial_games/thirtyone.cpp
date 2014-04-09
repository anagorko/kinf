#include<iostream>
#include<stdlib.h>
#include<unistd.h>
using namespace std;

int ile_pozycji = 0;

bool is_p(int na, int n2, int n3, int n4, int n5, int n6, int s)
{
    ile_pozycji++;
    
    if (s > 31) { return false; }
    
    if (na > 0) {
        if (is_p(na - 1,n2,n3,n4,n5,n6,s+1)) {
            return false;
        }
    }
    
    if (n2 > 0) {
        if (is_p(na,n2 - 1,n3,n4,n5,n6,s+2)) {
            return false;
        }
    }
    
    if (n3 > 0) {
        if (is_p(na,n2,n3 - 1,n4,n5,n6,s+3)) {
            return false;
        }
    }

    if (n4 > 0) {
        if (is_p(na,n2,n3,n4-1,n5,n6,s+4)) {
            return false;
        }
    }
    
    if (n5 > 0) {
        if (is_p(na,n2,n3,n4,n5-1,n6,s+5)) {
            return false;
        }
    }
    
    if (n6 > 0) {
        if (is_p(na,n2,n3,n4,n5,n6-1,s+6)) {
            return false;
        }
    }
    
    return true;
}

void wypisz_pozycje(int n[6], int s)
{
    cout << "Pozycja " << n[0] << " asów, " << n[1] << " dwójek, " << n[2] << " trójek, " <<
            n[3] << " czwórek, " << n[4] << " piątek, " << n[5] << " szóstek, suma " << s << ". ";
    
}

int ruch_komputera(int n[6], int s)
{
    int r;
    
    for (int i = 0; i < 6; i++) {
        if (n[i] > 0) {
            n[i]--; s += i + 1;
            if (is_p(n[0],n[1],n[2],n[3],n[4],n[5],s)) {
                cout << "PRZEGRAŁEŚ!!!!" << endl;
                n[i]++; s -= i + 1;
                return i + 1;
            }
            n[i]++; s -= i + 1;
        }
    }
    
    do {
        r = random() % 6;
    } while (n[r] == 0);
    
    return r+1;
}

int main()
{
    srandom(getpid() + time(NULL));
    
    int n[6];
    int s = 0;
    
    for (int i = 0; i < 6; i++) {
        n[i] = 4;
    }
    
    int nr_g = 1;
    
    while (s <= 31) {
        int r;
        while (true) {        
            cout << "Gracz " << nr_g << ". ";
            wypisz_pozycje(n, s);
            cout << "Twój ruch (1-6)?";
            cin >> r;
            if (r == 0) {
                for (int i = 0; i < 6; i++) {
                    if (n[i] > 0) {
                        n[i]--; s += i + 1;
                        if (is_p(n[0],n[1],n[2],n[3],n[4],n[5],s)) {
                            cout << (i+1) << "W  ";
                        } else {
                            cout << (i+1) << "P  ";
                        }
                        n[i]++; s -= i + 1;
                    }
                }
                cout << endl;                
                continue;
            }
            if (r < 1 || r > 6) {
                cout << "Podaj liczbę od 1 do 6."<< endl;
                continue;
            }
            if (n[r-1] > 0) break;
            cout << "Nie masz tej karty." << endl;
        }
    
        n[r-1]--; s += r;
        nr_g = 3 - nr_g; 
 
        if (s > 31) break;
        
        r = ruch_komputera(n, s);
        cout << "Ruch komputera: " << r << endl;
        
        n[r-1]--; s += r;
        nr_g = 3 - nr_g;
    }
    if (nr_g == 2) {
        cout << "PRZEGRAŁEŚ!!!" << endl;
    } else {
        cout << "WYGRAŁEŚ!!!!" << endl;
    }
}
