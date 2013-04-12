// (c) by Jan Kacprzak

#include<iostream>
using namespace std;
int main (){
int had = 0, have = 1,x , suma, parzy ;
	
	for (; parzy < 4000000;){ 
		
		x = had + have;

		if (x % 2 == 0){
			parzy += x; 
		}

		had = have;

		have = x;

		suma += x;
		
				
		
	}

	cout <<	endl << parzy << endl ;

return 0;
}
