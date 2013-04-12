#include<iostream>
using namespace std;
int main(){
	int n,q;
	cin>>n;//wczytywanie ilosci
	int t[n];
	int suma=0,ilosc,max=0;
	for(int i=0;i<n;i++){//wczytywanie liczb
		cin>>t[i];
	}
	for(int i=0;i<n;i++){//sprawdzanie...
	suma=t[i];
	ilosc=0;
	q=i;
		if(suma==1){
			for(q=i;q<n && t[q]==1;q++){
				ilosc++;
			}
			if(t[q]==1){cout<<max<<endl;return 0;}
			suma=t[q];
		}
		for(int a=q;a<n;a++){
			if(t[a]==1){ilosc++;continue;}
			if((suma & t[a])==0){continue;}
			if((suma & t[a])==suma || (suma & t[a])==t[a]){
				cout<<"dla i= "<<i<<" przeszła cyfra: "<<t[a]<<" ilosc= "<<ilosc+1<<endl;
				suma=(suma & t[a]);
				ilosc++;
			}
		}
		if(ilosc>max){max=ilosc;}
	}
	cout<<max;
return 0;
}
