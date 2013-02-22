#include<iostream>
#include<iomanip>
using namespace std;
int main(){
	cout<<"ile wyrazow sumowac?";
	long long int i;
	cin>>i;

	int z = 1;
	int m = 1;

	double s=0;

	cout<<"4*(";

	for(int w=0;w<i;w++){
	 s=s+(double)z*1/m;

	 if (z == 1){
		cout<<"+1/"<<m;
	}else{
		cout<<"-1/"<<m;
	}

	z=z*(-1);m=m+2;
	}

	cout<<")="<<fixed<<setprecision(10)<<4*s<<endl;

	return 0;
}
