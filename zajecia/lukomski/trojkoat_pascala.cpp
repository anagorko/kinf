#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	long long int t[n][n];
	t[0][0]=1;
	for(int i=1;i<n;i++){
		t[i][0]=1;
		t[i][i]=1;
		for(int a=1;a<i;a++){
			t[i][a]=t[i-1][a]+t[i-1][a-1];
		}
	}
	for(int i=0;i<n;i++){
		for(int a=0;a<=i;a++){
			cout<<t[i][a]<<" ";
		}
		cout<<"\n";
	}
return 0;
}
