#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	string a[n];
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	int przec[n];
	bool dodatni[n];
	int dodatnie=0;
	bool wiekszypierwszy;
	for(int i=0;i<n;i++){//szukanie przecinka
		if(a[i][0]=='+'){dodatni[i]=true;dodatnie++;}
		if(a[i][0]=='-'){dodatni[i]=false;}
		if(a[i][0]!='+' && a[i][0]!='-'){dodatni[i]=true;dodatnie++;}
		przec[i]=-1;
		for(int q=0;q<a[i].length();q++){
			if(a[i][q]==',' || a[i][q]=='.'){
				przec[i]=q;
				cout<<"przecinek nr "<<i<<" jest na miejscu "<<q<<" z "<<a[i].length()<<" miesjsc"<<endl;
				break;
			}
		}
	}
	int asdf[dodatnie][200];
	int asdfg[n-dodatnie][200];
	for(int i=0;i<200;i++){
		for(int q=0;q<dodatnie;q++){
			asdf[q][i]=0;
		for(int q=0;q<n-dodatnie;q++){
			asdfg[q][i]=0;
		}	
	}
		}
	for(int i=0;i<n;i++){
		if(dodatni[i]){
			if(przec[i]==-1){
				for(int q=a[i].length()-1;q>=0;q--){
					asdf[i][100-q]=(int)a[i][a[i].length()-1-q]-'0';
				}
			}else{
				for(int q=przec[i]-1;q>=0;q--){
				asdf[i][100-q]=(int)a[i][przec[i]-1-q]-'0';
				}
				for(int q=1;q<a[i].length()-przec[i];q++){
					asdf[i][100+q]=(int)a[i][przec[i]+q]-'0';
				}
			}
		}else{
			if(przec[i]==-1){
				for(int q=a[i].length()-1;q>=0;q--){
                     			asdfg[i][100-q]=(int)a[i][a[i].length()-1-q]-'0';
                      	}

			}else{
				for(int q=przec[i]-1;q>=0;q--){
              	        	asdfg[i][100-q]=(int)a[i][przec[i]-1-q]-'0';
               	        }
              	        for(int q=1;q<a[i].length()-przec[i];q++){
                	        	asdfg[i][100+q]=(int)a[i][przec[i]+q]-'0';
              	        }
			}
		}
	}
	for(int i=0;i<n-dodatnie;i++){
		cout<<i<<"to sie rowna:\n";
		for(int q=0;q<200;q++){
			cout<<asdfg[i][q]<<" ";
			if(q%50==0 && q!=0){cout<<endl;}
		}
		cout<<endl;
	}
	cout<<endl;
		for(int i=199;i>=0;i--){
			int suma=0;
			for(int q=0;q<dodatnie;q++){
				suma=suma+asdf[q][i];
			}
			if(suma>10){
				asdf[dodatnie-1][i]=suma%10;
				suma=(suma-(suma%10))/10;
			}else{
				asdf[dodatnie-1][i]=suma;
				suma=0;
			}
		}
		int suma=0;
		for(int i=199;i>=0;i--){
			for(int q=0;q<n-dodatnie;q++){
				suma=suma+asdfg[q][i];
			}
			if(suma>10){
				asdfg[n-dodatnie-1][i]=suma%10;
				suma=(suma-(suma%10))/10;
			}else{
				asdfg[n-dodatnie-1][i]=suma;
				suma=0;
			}
		}
		for(int i=0;i<200;i++){
			if(asdf[dodatnie-1][i]>asdfg[n-dodatnie-1][i]){wiekszypierwszy=true;break;}
			if(asdf[dodatnie-1][i]<asdfg[n-dodatnie-1][i]){wiekszypierwszy=true;break;}
			if(i==199){cout<<"0"<<endl;return 0;}
		}
		if(wiekszypierwszy){
			int suma=0;
			for(int i=199;i>=0;i--){
				if(asdf[dodatnie-1][i]>asdfg[n-dodatnie-1][i]){
					asdf[dodatnie-1][i]=asdf[dodatnie-1][i]-asdfg[n-dodatnie-1][i];
				}else{
					asdf[dodatnie-1][i-1]--;
					asdf[dodatnie-1][i]=asdf[dodatnie-1][i]+10;
					asdf[dodatnie-1][i]=asdf[dodatnie-1][i]-asdfg[n-dodatnie-1][i];
				}
			}
		}else{
		  	int suma=0;
                        for(int i=199;i>=0;i--){ 
                                if(asdfg[n-dodatnie-1][i]>asdf[dodatnie-1][i]){
                                        asdf[dodatnie-1][i]=asdfg[n-dodatnie-1][i]-asdf[dodatnie-1][i];
                                }else{
                                        asdfg[n-dodatnie-1][i-1]--;
                                        asdf[dodatnie-1][i]=asdfg[n-dodatnie-1][i]+10;
                                        asdf[dodatnie-1][i]=asdfg[n-dodatnie-1][i]-asdf[dodatnie-1][i];
                                }
                        }
		}
		bool zera;
		for(int i=0;i<200;i++){
			if(asdf[dodatnie-1][i]!=0 && zera){zera=false;}
			if(zera){continue;}
			cout<<asdf[dodatnie-1][i];
		}
		cout<<endl;
	return 0;
}



