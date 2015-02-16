#include <iostream>
using namespace std;
int main(){
	int n;
	int wicemistrz = 0;
	int mistrz = 0;
	cin>>n;
	for(int i=0;i<n;i++){

		int liczba;

		cin>>liczba;

		if(liczba > mistrz){
			wicemistrz = mistrz;
			mistrz = liczba;
		}else if(liczba > wicemistrz){
			wicemistrz = liczba;
		}
	}
	cout<<wicemistrz<<endl;
	return 0;
}
