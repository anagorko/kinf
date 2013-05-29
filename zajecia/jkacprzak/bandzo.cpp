// (c) by jkacprzka

#include<iostream>
using namespace std;
int main () {
int n = 0;
int d = 0, wynik = 0, f;
cin >> n;
int x[n*2];
for (int i = 0; i < n*2; i++){
	cin >> x[i];
}
for (int k = 0; k < n*2; k++){
	if(x[k]%2==0){
		x[k]= x[k]*2+1;
	}
}
for (int j = 0; j < n*2; j++){
	if(x[j]%2==1){
		x[j]= x[j]*2;
	}
}


for (int s = 0; s < n*2; s++){
	if (s % 2 == 0){
		wynik = (x[s]+x[s+1]/2);
		s++;
	}else{
		wynik = (x[s]+x[s+1]/2);
		s++;
	}

}

cout<<wynik/n<<endl;

}
