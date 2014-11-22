#include<iostream>
using namespace std;
int main () {
	int n = 0, tresc = 0, numerp, numerf;
	bool win = false;
	cin >> n;
	int tab[n];
	for (int i = 0; i < n; i++){
		cin >> tab[i];
	}
	for (int k = 0; k < n; k++){
		
		
		
		numerf = k+1;
		numerp = k;
	//	cout << k << numerp << " " << numerf << endl;
		win = false;
		cout<< "i" << tab[k]<<"j"<<tab[numerp]<< endl;
		for (int bajtowka = 0; win != true;bajtowka++){
			if (tab[numerp] ==numerf){
				cout << bajtowka << endl;
				win = true;
			}else{
				cout << tab[k]<<"k"<<tab[numerp]<<endl;
				tresc = tab[numerp];
				cout<< "tresc "<< tab[numerp]<<endl;
				numerp = tab[tresc-1];
				cout <<" " <<numerp<<endl;
				numerf = numerp+1;
	//			cout << numerp << " " << numerf<<endl;
				
			}
			
		}
		//if ()
		
	}	



}
