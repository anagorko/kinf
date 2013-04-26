#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Użycie: ./generator ile_liczb [ zakres ]" << endl;
        return 1;
    }
    
    int ile = atoi(argv[1]);
    int zakres = 1000000000;
    
    if (argc > 2) {
        zakres = atoi(argv[2]);
    }
    
    if (argc > 3) {
        srandom(atoi(argv[3]));
    } else {
        srandom(1234);
    }
    
    cout << ile << endl;
    for (int i = 0; i < ile; i++) {
        cout << (random() % zakres) << " ";
    }
    cout << endl;
    
    return 0;
}
