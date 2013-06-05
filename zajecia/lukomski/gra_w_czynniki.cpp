#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int t[n];
	int max=0;
	for(int i=0;i<n;i++){
		cin>>t[i];
		if(t[i]>max){max=t[i];}
	}
	int ta[max];
	bool czypier[max];
	int pier[max];
	int kon=0;
	for(int i=0;i<max/2;i++){//czyszczenie czypier(czy pierwsza);
		czypier[i]=true;
	}
	for(int i=2;i<max;i++){//sito arystotelesa
		if(czypier[i]=true){
			pier[kon]=i;
			kon++;
			for(int a=i;a<max;a=a+i){
				czypier[a]=false;
			}
		}
	}
//	cout<<"wypisywanie liczb pierwszych : ";
//	for(int i=0;i<kon;i++){//wypisywanie liczb pierwszych
//		cout<<pier[i]<<" ";
//	}
//	cout<<endl;
	///
	for(int i=0;i<max;i++){//rozwiazywanie tablicy
		ta[i]=0;
		for(int a=0;a<kon && pier[a]<i+1;a++){
			if(ta[i-pier[a]]==0 && (i+1)%pier[a]==0){ta[i]=1;break;}
		}
	}
//	cout<<"tablica : ";
//	for(int i=0;i<max;i++){
//		cout<<ta[i]<<" ";
//	}
	for(int i=0;i<n;i++){
		if(ta[t[i]-1]==1){cout<<"MAGDA\n";
		}else{
			cout<<"BARTEK\n";
		}
	}
	return 0;
}
