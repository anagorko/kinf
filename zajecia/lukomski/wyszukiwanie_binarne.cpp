#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<unistd.h>
using namespace std;
	int n=20;
int main(){
	vector<int> v;
	srandom(getpid());//indentyfikator PID
	for(int i=0;i<n;i++){
		v.push_back(random()%900+100);
	}
	sort(v.begin(),v.end());
	for(int i=0;i<n;i++){
		cout<<v[i]<<" ";
	}
	cout<<"\n";
	int x=100;
	cout<<"ABY WYJŚĆ Z PROGRAMU WPISZ '0'\n";
	while(true){
		cout<<"jakiej liczby szukać? ";
		cin>>x;
		if(x==0){break;}
		int a=0,s=n;
		bool wyjdz=false;
		while(a!=s){
			if(v[a+((s-a)/2)]==x){cout<<"jest liczba "<<x<<"\n";wyjdz=true;break;}
			if(v[a+((s-a)/2)]>x){s=a+((s-a)/2);}//cout<<"s== "<<s<<"\n";}
			if(v[a+((s-a)/2)]<x){a=a+((s-a)/2)+1;}//cout<<"a== "<<a<<"\n";}
		}
		if(!wyjdz && v[a]==x){cout<<"jest liczba "<<x<<"\n";
		}else if(!wyjdz){
			cout<<"nie ma liczby "<<x<<"\n";
		}
	}
	return 0;
}
