#include<iostream>
#include<string>
using namespace std;
string k;
void front_of_old_factory();
void bottom_of_stairs();

void boss_room()
{
	cout<<"Jesteś w ciemnym gabinecie. Przyciemniane okna przepuszczją pojedyńcze promienie słoneczne\n";
    while(true) {
        cout << "> ";
        getline(cin,k);

        if (k == "u" || k == "schody") {
            break;
        } else if (k == "wyjdź") {
            front_of_old_factory();
            break;
	}else if(k.substr(0,6) == "powrot"){
		if(k.substr(8,k.length()-1) == "bottom_of_stairs"){
			bottom_of_stairs();
		}else if(k.substr(8,k.length()-1) == "front_of_old_factory"){
			front_of_old_factory();
		}
        } else {
            cout << "Nie rozumiem tego polecenia.\n";
        }
    };
}

void bottom_of_stairs()
{
    cout << "Jesteś w hali produkcyjnej. Widzisz schody prowadzące do góry. Obok schodów jest przejście w kierunku północnym. Za tobą jest wyjście na zewnątrz.\n";

    string k;

    while(true) {
        cout << "> ";    
        getline(cin,k);

        if (k == "u" || k == "schody") {
		boss_room();
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
