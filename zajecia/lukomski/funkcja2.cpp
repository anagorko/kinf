#include<iostream>
using namespace std;
int min(int a, int b){
if(a>b){return b;}
if(b>a){return a;}
}
int main(){
int a,b;
cin>>a>>b;
cout<<min(a,b);
}
