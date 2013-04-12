#include<iostream>
using namespace std;
int main(){
	int t[200],ta[200],w[200];
	int kon,kon1;
	string s,s1;
	bool plus=true;
	cin>>s;
	cin>>s1;
	if(s.length()<s1.length()){plus=false;}
	if(s.length()==s1.length()){
		for(int i=0;i<s.length();i++){
			if((int)s[i]>(int)s1[i]){break;}
			if((int)s[i]<(int)s1[i]){plus=false;break;}
		}
	}
	if(!plus){
	kon=s1.length();
	kon1=s.length();
	}else{
	kon=s.length();
	kon1=s1.length();
	}
	for(int i=0;i<kon;i++){
		if(!plus){
			t[kon-i-1]=(int)s1[kon-i-1]-48;
			if(i<kon1){
				ta[kon-i-1]=(int)s[kon1-i-1]-48;
			}
		}
		if(plus){
			t[kon-i-1]=(int)s[kon-i-1]-48;
			if(i<kon1){
				ta[kon-i-1]=(int)s1[kon1-i-1]-48;
			}
		}
	}
	for(int i=0;i<kon-kon1;i++){//zerownie tego co trzeba
		ta[i]=0;
	}
	for(int i=kon-1;i>=0;i--){//odjmowanie
		if(t[i]<ta[i]){t[i]=t[i]+10;t[i-1]--;}
		w[i]=t[i]-ta[i];
	}
	//////////////////////endl of odejmowanie
	while(w[0]==0){//usuwnie zer z wyniku
		for(int q=0;q<kon-1;q++){
			w[q]=w[q+1];
		}
		kon--;
	}
	if(!plus){cout<<"-";}//wpisywnie minusa jezeli jest ujemna liczba
		//wpisywnie wyniku
		for(int q=0;q<kon;q++){
			cout<<w[q];
		}
		cout<<endl;
}
