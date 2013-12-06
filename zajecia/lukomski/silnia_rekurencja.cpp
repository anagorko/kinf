#include<iostream>
using namespace std;
long long int w=1;
int rekurencja(int n){
	w=w*n;
//	cout<<"n= "<<n<<", a w= "<<w<<endl;
	n--;
	if(n>1){
		rekurencja(n);
	}
	return w;
}
int main(){
	cout<<"obliczyc silnie z jakiej liczby ? ";
	long long int n;
	cin>>n;
	cout<<rekurencja(n)<<"\n";
	return 0;
}
