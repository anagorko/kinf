#include<iostream>
using namespace std;
int main() {
int n ;
cin >> n;
int t[n+1];
for (int i = 1; i < n+1; i++){
	int x =i;
	cin >> t[i];
	while (t[x] < t[x/2]){
		swap(t[x],t[x/2]);
		x = x/2;
	}
cout<< t[x]<<endl;
}
while ()
}
