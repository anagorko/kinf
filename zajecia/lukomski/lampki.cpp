#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int h;
	bool blad;
	for(int i=0;i<n;i++){
		blad=false;
		cin>>h;
		string s[h];
		int t[h][h];
		for(int a=0;a<h;a++){
			cin>>s[a];
			for(int q=0;q<h;q++){
				t[a][q]=(int)s[a][q]-48;
			}
		}
		/////////////////////////wypisuje co wpisal do tablicy t...
//		cout<<endl;
//		for(int a=0;a<h;a++){
//			for(int q=0;q<h;q++){
//			cout<<t[a][q]<<" ";
//			}
//			cout<<endl;
//		}
		/////////////////////////end of this
		/////////////////////sprawdzanie pierwszego wiersza
		for(int a=0;a<h;a++){
			if(t[a][0]!=1){
				for(int q=0;q<h;q++){
					t[a][q]=(t[a][q]+1)%2;
				}
			}
		}
		////////////////////end of sprawdzanie kolmuny;
		for(int a=0;a<h;a++){
			for(int q=1;q<h;q++){
				if(t[a][q]==0){
					for(int qw=0;qw<h;qw++){
						t[qw][q]=(t[qw][q]+1)%2;
					}
				}
			}
		}
		for(int a=0;a<h;a++){
			for(int q=0;q<h;q++){
				if(t[a][q]!=1){
					cout<<"NIE"<<endl;
					blad=true;
					break;
				}
			if(blad){break;}
			}
		if(blad){break;}
		}
		if(!blad){cout<<"TAK"<<endl;}
	}
return 0;
}
