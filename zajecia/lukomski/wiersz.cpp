#include<iostream>
using namespace std;
int main(){
	int n;//liczba par wersow do sprawdzenia
	int k;//dlugosc fragmentow koncowych
	int kon1,kon2;
	int w=0;
	cin>>n>>k;
	cin.ignore();
	for(int i=0;i<n;i++){
		string wie1;
	        string wie2;
		int czy=true;
		int sam1=0,sam2=0;//"sam" jak samogloski
		getline(cin, wie1);
		getline(cin, wie2);
		kon1=wie1.length();
		kon2=wie2.length();
		if(kon1<k || kon2<k){continue;}
		//czyszczenie ze spacji
		for(int a=0;a<kon1;a++){
			if(wie1[a]==' '){
				for(int b=a;b<kon1-1;b++){
					wie1[b]=wie1[b+1];
				}
			kon1--;
			}
			if(wie1[a]=='a' || wie1[a]=='e' || wie1[a]=='i' || wie1[a]=='o' || wie1[a]=='u' || wie1[a]=='y'){sam1++;}
		}
		for(int a=0;a<kon2;a++){
			if(wie2[a]==' '){
                                for(int b=a;b<kon2-1;b++){
                                        wie2[b]=wie2[b+1];
                                }
                        kon2--;
			}
			if(wie2[a]=='a' || wie2[a]=='e' || wie2[a]=='i' || wie2[a]=='o' || wie2[a]=='u' || wie2[a]=='y'){sam2++;}
		}
		if(sam1!=sam2){continue;}
		//end of czyszczenie ze spacji
		//sprawdzanie czy ostatnie k litery sie zgadzaja
		for(int x=0;x<k;x++){
			if(wie1[kon1-1-x]!=wie2[kon2-1-x]){czy=false;break;}
			}
		//end of sprawdzanie czy ostatnie k litery sie zgadzaja
		if(czy){w++;}
	}
	cout<<w<<endl;
}

