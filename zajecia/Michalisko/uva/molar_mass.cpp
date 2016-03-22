#include<iostream>
#include<ctype.h>
using namespace std;

int main(){
	int il;
	cin >> il;
	for(int i=il; i>0;i--){
		string in;
		cin >> in;
		int dl;
		dl= in.length();
		float a=0.0,b=0.0, m=0.0;
		int f;
		for(int j=0;j<=dl;j++){
			if(in[j]=='1' && f==0){
				a=a*1;
				f++;}
			else if(in[j]=='1' && f==1)
				a=a*10+(1*m);
			else if(in[j]=='2' && f==0){
				a=a*2;
				f++;}
			else if(in[j]=='2' && f==1)
				a=a*10+(2*m);
			else if(in[j]=='3' && f==0){
				a=a*3;
				f++;}
			else if(in[j]=='3' && f==1)
				a=a*10+(3*m);
			else if(in[j]=='4' && f==0){
				a=a*4;
				f++;}
			else if(in[j]=='4' && f==1)
				a=a*10+(4*m);
			else if(in[j]=='5' && f==0){
				a=a*5;
				f++;}
			else if(in[j]=='5' && f==1)
				a=a*10+(5*m);
			else if(in[j]=='6' && f==0){
				a=a*6;
				f++;}
			else if(in[j]=='6' && f==1)
				a=a*10+(6*m);
			else if(in[j]=='7' && f==0){
				a=a*7;
				f++;}
			else if(in[j]=='7' && f==1)
				a=a*10+(7*m);
			else if(in[j]=='8' && f==0){
				a=a*8;
				f++;}
			else if(in[j]=='8' && f==1)
				a=a*10+(8*m);
			else if(in[j]=='9' && f==0){
				a=a*9;
				f++;}
			else if(in[j]=='9' && f==1)
				a=a*10+(9*m);
			else{
				if(in[j]=='C'){
					b=b+a;
					a=12.01;
					m=a;
					f=0;}
				if(in[j]=='H'){
					b=b+a;
					a=1.008;
					m=a;
					f=0;}
				if(in[j]=='O'){
					b=b+a;
					a=16.0;
					m=a;
					f=0;}
				if(in[j]=='N'){
					b=b+a;
					a=14.01;
					m=a;
					f=0;}
			}
			
		}
		cout << b+a << endl;
	}
}
