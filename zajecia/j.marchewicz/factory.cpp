// (C) by Jan Marchewicz

#include<iostream>
using namespace std;

int terminal = 0;
int coin =0;
int candy = 0;

void front_of_old_factory();
void bottom_of_stairs ();
void top_of_basement_steps();
void damp_cellar();
void storeroom();
void landing ();
void manufacturing_area();
void cafeteria();
void landing_on_3rd_floor();



void front_of_old_factory()
{
    cout << "Stoisz przed bramą starej fabryki.\n";
    
    string k;

    while(true) 
	{
        	cout << "> ";    
        	getline(cin,k);
        
        	if (k == "wejdź") 
		{
           		bottom_of_stairs ();
			break;
        	} 
		else 
		{
            		cout << "Nie rozumiem tego polecenia.\n";
        	}
    };
    
   
}

void bottom_of_stairs()
{
    cout << "Jesteś w hali produkcyjnej. Widzisz schody prowadzące do góry. Obok schodów jest przejście w kierunku północnym. Za tobą jest wyjście na zewnątrz.\n";

    string k;

    while(true) 
	{
        	cout << "> ";    
        	getline(cin,k);
        
        	if (k == "u" || k == "schody") 
		{
           	 landing();
            	break;
        	} 
		else if (k == "wyjdź") 
		{
            		front_of_old_factory();
            		break;
        	} 
		else if (k== "północ" ) 
		{
			top_of_basement_steps();
			break;
		}
		else 
		{
           		cout << "Nie rozumiem tego polecenia.\n";
        	}
    };

}

void top_of_basement_steps ()
{
	cout<< "Znajdujesz się na szczycie schodów, prowadzących w dół\n";

	string k;

    while(true) 
	{
        	cout << "> ";    
        	getline(cin,k);
        
        	if (k == "zejdź" || k == "schody" || k== "dół" )
		{
			damp_cellar();
			break;
		}
		else if (k == "wróć" || k == " powrotem")
		{
			bottom_of_stairs();
			break;
		}
		else 
		{
			cout<< "Nie rozumiem polecenia!\n";
			
		}
	}
} 






void damp_cellar()
{
    cout << "Znajdujesz się w ciemnym, zatęchłym i wilgotnym pokoju ze śmiećmi. Przed tobą znajdują się drzwi.\n Uwaga na szczury mogą cię pogryźć!\n";
    
    string k;

    while(true) 
	{
       		cout << "> ";    
        	getline(cin,k);
        
        	if (k == "otwórz") 
		{
        	    	storeroom();
			break;
        	} 
		else if (k == "wróć" || k == "górę" || k == "schody") 
		{
			top_of_basement_steps();
			break;
		}
		else if (k == "info"  || k ==   "gdzie") 
		{
			cout<< "Znajdujesz się w ciemnym, zatęchłym i wilgotnym pokoju ze śmiećmi. Przed tobą znajdują się drzwi zamknięte na klucz.\n Uważaj na szczury! Mogą cię pogryźć.\n";
		}
		else 
		{
        	    cout << "Nie rozumiem tego polecenia.\n";
       		}
    	}	
    
     
}
void storeroom()
{
	cout<< "Jestes w magazynie, wszędzie są porozrzucane sprzęty, rupiecie, stare dokumenty. Kątem oka zauważasz biurko, na którym leży pendrive.\n";
}

void landing()
{
    cout << "Jesteś na półpiętrze. Zauważasz dwa pokoje: jeden w kierunku wschodnim, drugi zachodnim. Możesz pójść dalej schodami wzwyż\n";

	string k;
	while(true)
	{
		cout<< ">";
		getline(cin,k);
		
		if (k == "wschód")
		{
			manufacturing_area();
			break;
		}
		else if (k == "zachód")
		{
			cafeteria();
			break;
		}
		else if (k == "dalej" || k == "schody" || k == "góra")
		{
			landing_on_3rd_floor();
			break;
		}
		else 
		{
			cout<< "Nie rozumiem polecenia\n";
		}
	}
}

void cafeteria()
{
	cout<< "Wszedłeś/Weszłaś do opuszczonej kafejki. Na około widać puste stoliki i krzesła. Na końcu pomieszczenia przy ścianie stoi maszyna ze słodyczami. Podchodzisz do niej. Jest wyłączona.\n";
	
	string k;
	while(true)
		{
			cout<< ">";
			getline (cin,k);
			if (k == "wróć")
			{
				landing();
				break;
			}
			else if (k == "włącz")
			{
				cout<< "Włączyłeś maszynę.\n";
			}
			else if (k == "wrzuć" || k == "monetę" | k == "pieniążek")
			{
				if ( coin = 1)
				{
					cout<< "Po chwili myślenia maszyna wyrzuciła ci paczkę cukierków.\n";
					
				}
				else
				{
					cout << "Nie masz monet.\n";

				}
			}
			else if ( k == "weź" || k == "cukierki")
				{
					candy = 1;
				}
	
	
		}
}

void manufacturing_area()
{
	cout<<"Twoim oczom ukazuje się pomieszczenie produkcyjne. Potykasz się o torbę. Wydaje ci się ciekawa.\n";
	
	string k;
	while(true)
	{
		cout<< ">";
		getline (cin,k);
		
		if (k == "wróć")
		{
			landing();
			break;	
		}
		else if (k == "otwórz" || k == "torbę")
		{
			
			cout<< "Zauważasz interesującą końcówkę (możesz ją zbadać).\n";
		}
		else if (k == "badaj" || k == "zbadaj")
		{
			cout<< "Jest to mała końcówka wielkości paznokcia. Ma dwa wtyki z jednej strony, i mikrowyświetlacz z drugiej. Całośc została misternie wykonana.  W twoje oko wpadła też moneta. Zwykła dwuzłotówka. Chcesz je wziąć?\n";
		}
		else if ( k == "weź")
			{
				terminal = 1;
				coin = 1;
				cout<< "Wziąłeś końcówkę i monetę.\n";
				
			}
			
		else 
		{
			cout<< "Nie rozumiem polecenia.\n";
		}
	}

}


void landing_on_3rd_floor()
{
	cout << "Teraz jesteś na półpiętrze 3 piętra. Masz 2 możliwości: albo pójść do pokoju, który znajduje sie na wschód od ciebie albo piąć się dalej wzwyż. Co wybierasz?\n";

}

int main()
{
    front_of_old_factory();
    
    return 0;
}
