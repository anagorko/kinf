#include<iostream>
using namespace std;
int main(){
int n=0, licz = 1,mian = 1, x = 0;
cin >> n;
long long int tab[n], tabb[n];
for (int i = 0; i < n; i++){
	cin >> tab[i];
	cin >> tabb[i];
}
for (int i = 0;i < n;i++){
licz *= tab[i]; 
mian *= tabb[i];

}

if (mian % licz< mian && licz > 1 ){
	x = licz;
	licz =1;
	mian /= x;
	
}
cout<<licz<<"\\"<< mian<<endl; 
}
