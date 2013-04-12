#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int n,m;
    double a[100],wynik;
    cin >> n >> m;
    wynik = 0;
    for (int i = 0; i < n; i++){
       
		cin >> a[i];
        wynik = wynik+pow(a[i],m);
    }
    printf("%.3f", wynik);	/*bez tego program nie chciał działac to dodaje trzecia liczbę po przecinku do 								wyniku, kiedy robilem double a[n] też nie dzialał ??? */
    cout<<endl;
}
