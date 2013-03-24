#include <iostream>
using namespace std;

int main(){

int n;    
cin >> n;
int tab[n];
	
	for(int i = 0; i < n; i++){  
	
	cin>>tab[i]; 			//nadajemy wartosci poszczególnym elementom tablicy

	}

	for(int j = 0; j < n; j++ ){

		
	int suma = 0;	
		for(int k = 0 ; k <= j ; k++){

                    suma = suma + tab[k];
		}
	cout << suma << " ";  
	}
cout << endl;
}
