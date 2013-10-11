#include<iostream>
using namespace std;
int main(){
long long int figury[6]={1,1,2,2,2,8};
int n[6];
for (int i = 0; i< 6; i++){
	cin >> n[i];
	figury[i] -= n[i];
	cout << figury[i]; 
	if (i != 5){
		cout<<" ";
	}	
}
cout << endl;



}
