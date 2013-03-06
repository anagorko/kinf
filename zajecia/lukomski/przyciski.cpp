#include<iostream>
using namespace std;
int main(){
        int n;
        int m;
        int max=0;
        cin>>n>>m;
        int t[n];
        for(int i=0;i<n;i++){t[i]=0;}
        for(int i=0;i<m;i++){
                int p;
                cin>>p;
                if(p==n+1){
                        for(int a=0;a<n;a++){t[a]=max;}
                }else{
                        t[p-1]++;
                        if(t[p-1]>max){max=t[p-1];}
                }
        }
        for(int i=0;i<n;i++){
        cout<<t[i]<<" ";
        }
        cout<<endl;
}



