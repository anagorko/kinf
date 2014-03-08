#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main(){
	int n;
	int l=0,p=0;
	cin>>n;
	vector<int> t;
	int ta[2*n];
	int pocz=0;
	for(int i=0;i<2*n;i++){
		int a;
		cin>>a;
		t.push_back(a);
	}
	sort(t.begin(),t.end());
	for(int i=0;i<2*n;i++){
			cout<<t[i]<<" ";
		}
		cout<<"\n";
	for(int i=0;i<2*n;i++){
		int a=1;
		while(t[i]==t[i+1]){
			a++;
			i++;
		}
		if(a%2==1){
			ta[pocz]=t[i];
			pocz++;
		}
	}
	if(pocz>3 || n==1){cout<<"NIE\n";
	}else if(pocz==0){
		cout<<t[0]<<" "<<t[1]<<"\n";
	}else{
		if(ta[0]<ta[1]){cout<<ta[0]<<" "<<ta[1]<<"\n";
		}else{
			cout<<ta[1]<<" "<<ta[0]<<"\n";
		}
	}
	return 0;
	}
	

