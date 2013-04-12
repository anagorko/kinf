#include<iostream>
using namespace std;
int main(){
	int n,kon=0;;
	int t[100000];
	bool ta[100002];
	bool pierwsza=true,exit=false;
	for(int i=0;i<100002;i++){
		t[i]=0;
		ta[i]=false;
	}
	t[1]=1;
	for(int i=2;i<100002;i++){
		if(!ta[i]){
			t[kon]=i;
			kon++;
			for(int a=i;a<100002;a+=i){
				ta[a]=true;
			}
		}
	}
	/////////////////
//	for(int i=0;i<100;i++){
//		cout<<t[i]<<endl;
//	}
	////////////////
	cin>>n;
	int x;
	for(int i=0;i<n;i++){
		exit=false;
		cin>>x;
		int tab[x+1];
		tab[1]=0;//1
		tab[2]=0;//2
		tab[3]=0;//3
		for(int a=0;t[a]<=x;a++){
			tab[a]=0;
			if(t[a]==x){cout<<"Bartek\n";pierwsza=false;break;}
		}
		if(!pierwsza){pierwsza=true;continue;}
		for(int a=4;a<=x && tab[a]!=0;a++){
			pierwsza=true;
			for(int q=0;t[q]<x;q++){
				if(tab[a-t[q]]==0){
					pierwsza=false;
					tab[a]=1;
					cout<<"tab["<<a<<"]= "<<tab[a]<<endl;
					if(a==x){cout<<"MAGDA\n";exit=true;break;}
				break;
				}
			}
			if(exit){break;}
			if(pierwsza){
				t[a]=0;
				if(a==x){cout<<"BARTEK\n";break;}
			}
		}
	}
return 0;
}
