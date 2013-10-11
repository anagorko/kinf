#include<iostream>
using namespace std;
int main(){
int n[5], wynik = 0;
for (int i = 0; i < 5;i++){
	cin >> n[i];
	wynik += n[i];
}

cout << wynik/3 << endl;

}
