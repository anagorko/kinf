#include<iostream>
using namespace std;
int main (){
int x, wynik = 0;
cin >> x; 
string ab;
cin >> ab;
for(int i = 0; i < ab.length();i++ ){
	if(ab[i] == 'a'){
		if(ab[i+1] == 'b'){
			wynik += 1;
			i += 1;
		} else {
			wynik += 1;
		}
	}else{
		if(ab[i+1]== 'a'){
			wynik += 1;
			i += 1;
		}else{
			wynik += 1;
		} 
	}
}



cout << wynik << endl;	

}
