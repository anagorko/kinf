#include<iostream>
using namespace std;
int main(){
	int h;
	cin>>h;
	for(int i=h-1;i>0;i--){
		for(int a=i;a>=0;a--){
			cout<<"T";
		}
		cout<<"\n";
	}
	for(int i=1;i<=h;i++){
                for(int a=1;a<=i;a++){
                        cout<<"T";
                }
                cout<<"\n";
        }
	return 0;
}

