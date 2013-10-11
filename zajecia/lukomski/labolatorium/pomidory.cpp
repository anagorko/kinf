#include<iostream>
using namespace std;
int main(){
	string a;
	cin>>a;
	int t[a.length()+1];
	int zapamietane=0;
	for(int i=a.length()-1;i>=1;i--){
		t[i+1]=(int)a[i]-48;
		t[i+1]=t[i+1]*2+zapamietane;
		if(t[i+1]>=10){
			zapamietane=(t[i+1]-(t[i+1]%10))/10;
			t[i+1]=t[i+1]%10;
		}else{
			zapamietane=0;
		}
	}
	t[1]=((int)a[0]-48)*2+zapamietane;
	if(t[1]>10){
		t[0]=(t[1]-t[1]%10)/10;
		t[1]=t[1]%10;
	}else{
		t[0]=0;
	}
	if(t[0]!=0){cout<<t[0];}
	for(int i=1;i<a.length()+1;i++){
		cout<<t[i];
	}
	cout<<endl;
	return 0;
}
