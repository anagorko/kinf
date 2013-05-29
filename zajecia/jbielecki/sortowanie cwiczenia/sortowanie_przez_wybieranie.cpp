#include  <iostream>
using namespace std;

int main(){

    int n;
	int zmienna_pomocnicza;
	cin >> n;	
    int tab[n];
    for(int i = 0; i < n; i++) {
	cin >> tab[i];
    }
    for(int i = 0; i < n; i++) {
        int k = i;
        for(int j = i + 1; j < n; j++) if(tab[j] < tab[k]) k = j;
    	zmienna_pomocnicza = tab[i];
		tab[i] = tab[k];
		tab[k] = zmienna_pomocnicza;  
    }
    for(int i = 0; i < n; i++){
	cout << tab[i] << " ";
	}
    cout << endl;
    return 0;
}
