#include<iostream>
using namespace std;
int main(){
	int n,ta;
	cin>>n;
	int t[n];
	bool pierwsza;
	for(int i=0;i<n;i++){
		pierwsza=true;
		cin>>ta;
		if(ta==1 || ta==2 || ta==3){cout<<"BARTEK"<<endl;continue;}
		t[0]=0;
		t[1]=0;
		t[2]=0;
		for(int a=3;a<ta;a++){
			pierwsza=true;
			for(int q=a;q>1;q--){
				if((a+1)%q==0){
					t[a]=(t[q-1]+1)%2;
					cout<<"t["<<a<<"] = "<<t[a]<<endl;
					pierwsza=false;
					break;
				}
			}
			if(pierwsza){t[a]=0;}
		}
		if(t[ta-1]==0 || pierwsza){cout<<"BARTEK"<<endl;}
		if(t[ta-1]==1){cout<<"MAGDA"<<endl;}
	}
return 0;
}
