#include<iostream>
using namespace std;
int main(){
	int p[200];
	int d[200];
	for(int i=0;i<200;i++){
		p[i]=0;
		d[i]=0;
	}
	string ps,ds;
	cin>>ps>>ds;
	int pa=ps.length()-1,da=ds.length()-1;
	for(int i=199;i>=0;i--){
		if(199-i<ps.length()){
			p[i]=(int)ps[pa]-'0';
			pa--;
		}
		if(199-i<ds.length()){
			d[i]=(int)ds[da]-'0';
			da--;
		}
	}
	cout<<"p:\n";
	for(int i=0;i<200;i++){
		cout<<p[i];
	}
	cout<<endl;
	cout<<"d:\n";
	for(int i=0;i<200;i++){
		cout<<d[i];
	}
	cout<<"\n";
	//dodawanie
	int przejscie=0;
	for(int i=199;i>=0;i--){
		if(p[i]+d[i]>=10){
			przejscie++;
			p[i-1]=p[i-1]+((p[i]+d[i])-((p[i]+d[i])%10))/10;
		}
	}
	cout<<przejscie<<"\n";
	return 0;
}



