#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
using namespace std;
	int n=5;
int main(){
	vector<int> v;
	srandom(7);
	for(int i=0;i<n;i++){
		v.push_back(random()%1000+100);
	}
	sort(v.begin(),v.end());
	for(int i=0;i<n;i++){
		cout<<v[i]<<" ";
	}
	cout<<"\n";
	int i=100;
	while(i>=100){

	}
	
