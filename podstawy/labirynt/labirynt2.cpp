#include<stdio.h>
#include<iostream>
using namespace std;

int main()
{
	char odp = '\n';

	cout<<("LABIRYNT\n");
	cout<<("--------\n\n");
	cout<<"...jestes w pokoju stoi tam sejf i biurko z krzeslem, przed toba sa dwoje drzwi. Co robisz wchodzisz do pierwszych (1), drugich (2) czy siadasz przy biurku(s)?\n\n";

	do { cin>>odp; } while ( odp == '\n' );

	if (odp==1||odp==2){
		cout<<"wszedles do lochu i przegrales\n\n";
		return 0;
	}
	if (odp == 's'){
		cout<<"wpadles z krzeslem do komnaty ponizej, na nieszczescie spadles na kota, i go polamales."
		    <<" Ty i kot narobiliscie troche za duzo halasu, uslyszales kroki na korytazu\n\n";
	}
	cout<<"Do pokoju wpadlo trzech rycerzy, walczysz (w) czy skaczesz przez okno (k).\n\n";

	do { cin>>odp; } while ( odp == '\n' );

	if (odp == 'w'){
		cout<<"zabito cie\n\n";
	}
	if (odp == 'k'){
		cout<<"miales szczescie! Spadles na woz z sianem.\n\n";
	}
	cout<<"Na dziedzincu nikogo nie ma. Czekasz jeszcze (c) czy prubujesz uciec (u)?\n\n";
	do { cin>>odp; } while ( odp == '\n' );
	if (odp == 'c'){
		cout<<"udalo ci sie!\n\n";
	}	
	do { cin>>odp; } while ( odp == '\n' );	
	if (odp == 'u'){
		cout<<"udalo ci sie!\n\n";
	}	
	return 0;
}
