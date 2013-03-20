#include<iostream>
using namespace std;
int main(){
	int m,n;
	cin>>n>>m;
	long long int t[n];
	/////////////////wczytywanie n
        for(int i=0;i<n;i++){
               cin>>t[i];
        }
	/////////////////end of wczytywanie n
	long long int ma,mini;
	int licz=0,qu;
	for(int i=0;i<m;i++){
		mini=1000000001;
		cin>>ma;
		for(int a=0;a<n;a++){
			if(t[a]<ma){continue;}
			if(t[a]==ma){licz++;t[a]=0;break;}
			if(t[a]<mini){
				for(int q=a;q<n;q++){
					if(t[q]<mini && t[q]>=ma){qu=q;mini=t[q];}
				}
				licz++;
				//cout<<"ma= "<<ma<<" t[qu]= "<<t[qu]<<"minni = "<<mini<<endl;
				t[qu]=0;
				break;
			}
		}
	}
	cout<<licz<<endl;
return 0;
}
