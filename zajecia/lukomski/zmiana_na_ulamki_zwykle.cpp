#include<iostream>
#include<sstream>
#include<math.h>
using namespace std;
int main(){
	int c;
	string cs;
	cin>>cs;
	istringstream ss(cs);
	ss >> c;
	int dlugosc=cs.length();
//	cout<<dlugosc<<endl;
	int l,m;
	m=pow(10, dlugosc)-1;
	l=c;
//	cout<<l<<" "<<m<<endl;
	int dzielnik;
	bool wyjsc=false;
	if(m!=0 && l!=0){
		while(!wyjsc){
			if(l>m){
				l=l%m;
				if(l==0){
					dzielnik=m;
					wyjsc=true;
				}
			}else{
				m=m%l;
				if(m==0){
					dzielnik=l;
					wyjsc=true;
				}
			}
		}
	}else if(m==0){dzielnik=l;
	}else if(l==0){dzielnik=m;}
	cout<<c/dzielnik<<"/"<<(pow(10,dlugosc)-1)/dzielnik<<"\n";
	
}
