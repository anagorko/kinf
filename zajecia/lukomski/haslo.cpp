#include<iostream>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	string s;
	cin>>s;
	int t[s.length()];
	for(int i=1;i<s.length();i++){
		t[i]=((int)s[i]-'a')-((int)s[i-1]-'a');
		if(t[i]<0){t[i]=t[i]-t[i]-t[i];}
//		cout<<t[i]<<" ";
	}
	int pocz=1;
	int suma=0;
	int w=1;
	for(int i=1;i<s.length();i++){
		suma=suma+t[i];
		while(suma>k){
			suma=suma-t[pocz];
			pocz++;
		}
		if(w<i-pocz+2){w=i-pocz+2;}
	}
	cout<<w<<"\n";
	return 0;
}
