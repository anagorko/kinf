#include <iostream>
using namespace std;
int main () {
int ile;
cin >> ile;
long long int tablica[ile][2];
int last = -1;
for (int i = 0; i < ile; i++){
	long long int n;
	cin >> n;
	if(last != -1){
		if(tablica[last][0] == n){
			tablica[last][1]++;
		}else{
			last++;
			tablica[last][0] = n;
			tablica[last][1] = 1;
		}
	}else{
		last = 0;
		tablica[last][0] = n;
		tablica[last][1] = 1;
	}
}
int ilez;
cin >> ilez;
long long int tablicaz[ilez];
for (int i = 0; i < ilez; i++){
	cin >> tablicaz[i];
}
int najm = 0, najw = 0;
for (int i = 0; i < ilez; i++){
	najm = 0;
	najw = ile - 1;
	cout << endl << "#$$$ - " << tablicaz[i];
	for(; najm != najw;){
		cout << "#@@@ - " << najm << " " << najw << endl;
		if(tablica[najw - (najw - najm + 1)/2][0] == tablicaz[i]){
			najm = (najw - (najw - najm + 1)/2);
			break;
		}
		else if(tablica[najw - (najw - najm + 1)/2][0] > tablicaz[i]) najw = (najw - (najw - najm + 1)/2);
		else if(tablica[najw - (najw - najm + 1)/2][0] < tablicaz[i]) najm = (najw - (najw - najm + 1)/2);
	}
	
	if(tablica[najm][1] == tablicaz[i])cout << tablica[najm][1] << endl;
	else cout << 0 << endl;
}
}
