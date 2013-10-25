#include<iostream>
using namespace std;
int main(){
	int t[400];
	bool dodatni=true;
	for(int i=0;i<400;i++){
		t[i]=0;
	}
	while(true){
		bool dodatni1=true;
		int t1[400];
		for(int i=0;i<400;i++){
			t1[i]=0;
		}
		string s;
		getline(cin,s);
		if(s.length()==0){break;}
		int qw=s.length()-1;
		for(int i=399;qw>=0;i--){
			if(i==400-s.length()){
				if(s[0]=='-'){dodatni1=false;qw--;}
				if(s[0]=='+'){qw--;}
				if(qw>=0 && s[0]!='+' && s[0]!='-'){t1[i]=(int)s[qw]-'0';qw--;}
				break;
			}
			t1[i]=(int)s[qw]-'0';
			qw--;
		}
//	     	cout<<"t1[i]==::\n";
//             	for(int i=0;i<200;i++){
//             	cout<<t1[i];
//                }
//		cout<<"\n";

		if((dodatni && dodatni1) || (!dodatni && !dodatni1)){
//		cout<<"oba dodatnie\n";
			for(int i=399;i>=0;i--){
				if(t[i]+t1[i]>=10){
					t[i-1]=t[i-1]+(t[i]+t1[i]-((t[i]+t1[i])%10))/10;
					t[i]=(t[i]+t1[i])%10;
				}else{
					t[i]=t[i]+t1[i];
				}
			}
		}else{
			bool zero=false;
//			cout<<"jeden dodatni, a drugi ujemny\n";
			bool pierwszy_wiekszy=false;
			for(int i=0;i<400;i++){
				if(t1[i]<t[i]){pierwszy_wiekszy=true;break;}
				if(t[i]<t1[i]){break;}
				if(i==399){zero=true;}
			}
			if(!zero){
				if((dodatni && !dodatni1) || (!dodatni && dodatni1)){
					if(pierwszy_wiekszy){
						for(int i=399;i>=0;i--){
//							cout<<"aa";
							if(t[i]-t1[i]<0){
								t[i-1]--;
								t[i]=t[i]+10-t1[i];
							}else{
								t[i]=t[i]-t1[i];
							}
						}
					}else{
						for(int i=399;i>=0;i--){
//							cout<<"b";
							if(t1[i]-t[i]<0){
								t1[i-1]--;
								t[i]=t1[i]+10-t[i];
							}else{
								t[i]=t1[i]-t[i];
							}
						}
						if(dodatni){dodatni=false;
						}else{dodatni=true;}
					}
				}
			}else{
				for(int i=0;i<400;i++){
					t[i]=0;
				}
				dodatni=true;
			}
		}
//                cout<<"t1[i]==::\n";
//                for(int i=0;i<200;i++){
//                cout<<t1[i];
//                }
//                cout<<"\n t[i]==::\n";
//                for(int i=0;i<200;i++){
//                cout<<t[i];
//               }
//                cout<<"\n";

	}
	int licznik=0;
	while(licznik<400){
		if(t[licznik]!=0){break;}
		licznik++;
	}
	if(licznik==400){cout<<"0\n";return 0;}
	if(!dodatni){cout<<"-";}
	for(int i=licznik;i<400;i++){
		cout<<t[i];
	}
	cout<<"\n";
	return 0;
}

