#include<iostream>
using namespace std;

void front_of_old_factory();

void landing()
{
    cout << "...\n";
}

void bottom_of_stairs()
{
    cout << "Jesteś w hali produkcyjnej. Widzisz schody prowadzące do góry. Obok schodów jest przejście w kierunku północnym. Za tobą jest wyjście na zewnątrz.\n";

    string k;

    while(true) {
        cout << "> ";    
        getline(cin,k);
        
        if (k == "u" || k == "schody") {
            landing();
            break;
        } else if (k == "wyjdź") {
            front_of_old_factory();
            break;
        } else {
            cout << "Nie rozumiem tego polecenia.\n";
        }
    };

}

void front_of_old_factory()
{
    cout << "Stoisz przed bramą starej fabryki.\n";
    
    string k;

    while(true) {
        cout << "> ";    
        getline(cin,k);
        
        if (k == "wejdź") {
            break;
        } else {
            cout << "Nie rozumiem tego polecenia.\n";
        }
    };
    
    bottom_of_stairs();    
}

int main()
{
    front_of_old_factory();
    
    return 0;
}
