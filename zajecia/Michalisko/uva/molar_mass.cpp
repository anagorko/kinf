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
		float a=0.0,b=0.0;
		for(int j=0;j>=dl;j++){
			if(in[j]==1)
				a=a*in[j];
				cout << "jeden";
			if(in[j]=='2')
				a=a*in[j];
				cout << "dwa";
			if(in[j]=='3')
				a=a*in[j];
			if(in[j]=='4')
				a=a*in[j];
			if(in[j]=='5')
				a=a*in[j];
			if(in[j]=='6')
				a=a*in[j];
			if(in[j]=='7')
				a=a*in[j];
			if(in[j]=='8')
				a=a*in[j];
			if(in[j]=='9')
				a=a*in[j];
			else{
				if(in[j]=='C')
					a=12.01;
				if(in[j]=='H')
					a=1.008;
				if(in[j]=='O')
					a=16.0;
				if(in[j]=='N')
					a=14.01;
			}
			b=b+a;
		}
		cout << b;
	}
}
