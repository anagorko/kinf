#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
	vector<int>poczprzerw;
	vector<int>konprzerw;
	int n,t,d;
	cin>>n>>t>>d;
	int tn[n][2];
	int ochr[n][2];
	//wczytywanie ochroniarzy
	for(int i=0;i<n;i++){
		ochr[i][0]=-1;
		ochr[i][1]=0;
		int zmienna1;
		int zmienna2;
		cin>>zmienna1;
		cin>>zmienna2;
		poczprzerw.push_back(zmienna1);
		konprzerw.push_back(zmienna2);
	}
	//sortowanie
	sort(poczprzerw.begin(),poczprzerw.end());
	sort(konprzerw.begin(),konprzerw.end());
	//wypisywanie posortowanch liczb
//	cout<<"posortowane:\n";
//	for(int i=0;i<poczprzerw.size();i++){
//	cout<<poczprzerw[i]<<" "<<konprzerw[i]<<"\n";
//	}
//	cout<<"\n";
	//end of wypisywanie posortowanych liczb

//	DLA K=ZERO
//	cout<<"\n";
	if(d+1-t==0){return 0;
	}else{
		cout<<"0 "<<d+1-t<<"\n";
	}
//	DLA K>0
	int ilosc=0;
	int wa=0;// poczprzerw[]
	int we=0;//konprzerw[]
	bool wyjscie=false;
	while(we!=n){
//		cout<<"TABLICA OCHR[]\n";
//		for(int i=0;i<n;i++){
//			cout<<ochr[i][0]<<" "<<ochr[i][1]<<"\n";
//		}
//		cout<<"\n";
//		cout<<" "<<poczprzerw[wa]<<" vs "<<konprzerw[we];
		if(wa!=n){
			if(poczprzerw[wa]<=konprzerw[we]){
//				cout<<" => "<<poczprzerw[wa]<<"   wa<n \n";
				ilosc++;
				if(ochr[ilosc-1][0]==-1){
					ochr[ilosc-1][0]=poczprzerw[wa];
				}
				wa++;
				continue;
			}
			if(poczprzerw[wa]>konprzerw[we]){
				if(poczprzerw[wa]==konprzerw[we]+1){
					we++;
					ilosc--;
				}else{
//					cout<<" => "<<konprzerw[we]<<"   wa<n\n";
					if(konprzerw[we]-ochr[ilosc-1][0]+2-t>0){
						ochr[ilosc-1][1]=ochr[ilosc-1][1]+konprzerw[we]-ochr[ilosc-1][0]+2-t;
					}
					ochr[ilosc-1][0]=-1;
					ilosc--;
					we++;
				}
				continue;
			}
		}else{
//			cout<<" => "<<konprzerw[we]<<"   wa==n"<<endl;
			if(konprzerw[we]-ochr[ilosc-1][0]+2-t>0){
	              		ochr[ilosc-1][1]=ochr[ilosc-1][1]+konprzerw[we]-ochr[ilosc-1][0]+2-t;
                	}
                        ochr[ilosc-1][0]=-1;
                        ilosc--;
                        we++;
                        continue;
		}
	}
	for(int a=0;a<n;a++){
		if(ochr[a][1]==0){break;}
		cout<<a+1<<" "<<ochr[a][1]<<"\n";
	}
	return 0;
}
