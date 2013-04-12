#include<iostream>
using namespace std;
int main(){
	int n,x,c,a;
	cin>>n;
	bool magda,bez=true;
	for(int i=0;i<n;i++){
		magda=false;
		cin>>x;
		a=x-1;
		while(a>1){
			if(x%a==0){
				for(int q=2;q<x;q++){
					if((x/a)>3){bez=false;break;}
				}
				if(bez){
					x=x/a;
					if(magda){
						magda=false;
						cout<<"1a= "<<a<<endl;
					}else{
						magda=true;
						cout<<"2a= "<<a<<endl;
					}
					a=x-1;
				}
			}
			a--;
		}
		if(magda){cout<<"MAGDA\n";}
		if(!magda){cout<<"BARTEK\n";}
	}
return 0;
}
