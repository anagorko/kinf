#include<iostream>
using namespace std;
int main()
{
	long long int n;
		cin>>n;
	long long int t[n];
	bool ta[n];
	for(int i=0;i<n;i++){
		cin>>t[i];
		ta[i]=true;
	}
	for(int i=0;i<n;i++){
		if(ta[i]==false){continue;}
		for(int a=i+1;a<n;a++){
			if(t[a]==t[i] && ta[a]==true){
				ta[a]=false;
				cout<<t[a]<<" ";
				for(int q=a+1;q<n;q++){
					if(t[a]==t[q]){ta[q]=false;}
				}
			}
		}
	}
return 0;
}
