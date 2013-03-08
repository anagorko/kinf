#include<iostream>
using namespace std;
int main(){
        int n;
        int m;
        int max=0,min=0;;
        cin>>n>>m;
        int t[n];
        for(int i=0;i<n;i++){t[i]=0;}
        for(int i=0;i<m;i++){
                int p;
                cin>>p;
                if(p==n+1){
                        min=max;
                }else{
                        if(t[p-1]>min){t[p-1]++;
			}else{t[p-1]=min+1;}
                        if(t[p-1]>max){max=t[p-1];}
                }
	}
        for(int i=0;i<n;i++){
		if(t[i]>min){
        	cout<<t[i]<<" ";
       		}else{cout<<min<<" ";}
	}
        cout<<endl;
}



