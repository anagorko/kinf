#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	string s[n];
	bool dodatni[n];
	int dodatnie=0;
	int przec[n];
	int maxright=100;
	for(int i=0;i<n;i++){
		cin>>s[i];
		if(s[i][0]=='-'){dodatni[i]=false;}
		if(s[i][0]=='+'){dodatni[i]=true;dodatnie++;}
		if(s[i][0]!='-' && s[i][0]!='+'){dodatni[i]=true;dodatnie++;}
		przec[i]=-1;
		for(int q=0;q<s[i].length();q++){
                        if(s[i][q]==',' || s[i][q]=='.'){
                                przec[i]=q;
//                                cout<<"przecinek nr "<<i<<" jest na miejscu ";
                                break;
                        }
		}

	}
	int t[dodatnie][200];
	int ta[n-dodatnie][200];
	for(int i=0;i<200;i++){
		for(int a=0;a<n;a++){
			if(a<dodatnie || a==0){t[a][i]=0;}
			if(a<n-dodatnie || a==0){ta[a][i]=0;}
		}
	}
	int ujemnaliczba=0;
	int dodatnialiczba=0;
//	cout<<"dosedlem"<<endl;
	for(int i=0;i<n;i++){
		if(dodatni[i]){
			if(przec[i]==-1){
                                for(int q=s[i].length()-1;q>=0;q--){
					if(s[i][s[i].length()-1-q]=='+' || s[i][s[i].length()-1-q]=='-'){continue;}
                                	        t[dodatnialiczba][100-q]=(int)s[i][s[i].length()-1-q]-'0';
				}
                        }else{
                                for(int q=przec[i]-1;q>=0;q--){
					if(s[i][przec[i]-1-q]=='+' || s[i][przec[i]-1-q]=='-'){continue;}
                                		t[dodatnialiczba][100-q]=(int)s[i][przec[i]-1-q]-'0';
                                }
                                for(int q=1;q<s[i].length()-przec[i];q++){
					if(s[i][przec[i]+q]=='+' || s[i][przec[i]+q]=='-'){continue;}
                                 	       t[dodatnialiczba][100+q]=(int)s[i][przec[i]+q]-'0';
                                }
	               	}
			dodatnialiczba++;
		 }else{
                        if(przec[i]==-1){
                                for(int q=s[i].length()-1;q>=0;q--){
					if(s[i][s[i].length()-1-q]=='+' || s[i][s[i].length()-1-q]=='-'){continue;}
                                        ta[ujemnaliczba][100-q]=(int)s[i][s[i].length()-1-q]-'0';
                      		}
	 		}else{
                                for(int q=przec[i]-1;q>=0;q--){
					if(s[i][przec[i]-1-q]=='+' || s[i][przec[i]-1-q]=='-'){continue;}
                                	ta[ujemnaliczba][100-q]=(int)s[i][przec[i]-1-q]-'0';
                        	}
                        	for(int q=1;q<s[i].length()-przec[i];q++){
					if(s[i][przec[i]+q]=='+' || s[i][przec[i]+q]=='-'){continue;}
                                        ta[ujemnaliczba][100+q]=(int)s[i][przec[i]+q]-'0';
                        	}
                        }
			ujemnaliczba++;
                }
	}
//	cout<<"jestye"<<endl;
//	for(int i=0;i<dodatnie;i++){
//		for(int a=0;a<200;a++){
//			cout<<t[i][a];
//		}
//		cout<<endl;
//	}
//	cout<<"ujemne"<<endl;
//	for(int i=0;i<n-dodatnie;i++){
//		for(int a=0;a<200;a++){
//			cout<<ta[i][a];
//		}
//		cout<<endl;
//	}
	//sumowanie
	int t1[200];
	int ta1[200];
	for(int i=199;i>0;i--){
		if(dodatnie>0){
			int suma=0;
			for(int a=0;a<dodatnie;a++){
				suma=suma+t[a][i];
			}
			if(suma>=10){
				t[0][i-1]=t[0][i-1]+(suma-(suma%10))/10;
				suma=suma%10;
			}
			t1[i]=suma;
		}
		if(n-dodatnie>0){
			int suma=0;
			for(int a=0;a<n-dodatnie;a++){
				suma=suma+ta[a][i];
			}
			if(suma>=10){
				ta[0][i-1]=ta[0][i-1]+(suma-(suma%10))/10;
				suma=suma%10;
			}
			ta1[i]=suma;
		}
	}
//	cout<<"zsumowane:\n";
//	for(int i=0;i<200;i++){
//		cout<<t[0][i];
//	}cout<<"\nujemne:\n";
//	for(int i=0;i<200;i++){
//		cout<<ta[0][i];
//	}
//	cout<<"\nskonczylem sumowanie"<<endl;
	//sprawdzanie ktore jest wieksze
	bool wiekszypierwszy=false;
	if(dodatnie>0 && n-dodatnie>0){
		for(int i=0;i<200;i++){
	                        if(t1[i]>ta1[i]){wiekszypierwszy=true;break;}
	                        if(t1[i]<ta1[i]){wiekszypierwszy=false;break;}
	                        if(i==199){cout<<"0\n";return 0;}
		}
	}else if(dodatnie>0){wiekszypierwszy=true;}
	//odejmowanie wiekszego od mniejszego
	if(dodatnie>0 && n-dodatnie>0){
		if(wiekszypierwszy){
			int suma=0;
	                for(int i=199;i>=0;i--){
	         	      	if(t1[i]-ta1[i]>=0){
	                        	t1[i]=t1[i]-ta1[i];
	                       	}else{
	                	       	t1[i-1]--;
	                               	t1[i]=t1[i]+10;
	                               	t1[i]=t1[i]-ta1[i];
	                      	}
		               	}
       		}else{
      		      	int suma=0;
       		       	for(int i=199;i>=0;i--){ 
        			if(ta1[i]-t1[i]>=0){
                	        	t1[i]=ta1[i]-t1[i];
       	              		}else{
 	   	                   	ta1[i-1]--;
 	                         	t1[i]=ta1[i]+10;
 		       	          	t1[i]=ta1[i]-t1[i];
                	        }
       	         	}
   		}
	}else if(!wiekszypierwszy){
		cout<<"-";
	        int licznik=0;
	        while(ta1[licznik]==0){
	                licznik++;
	        }
	        for(int i=licznik;i<=100;i++){
	                cout<<ta1[i];
	        }
	        licznik=199;
	        while(t1[licznik]==0){
	                licznik--;
	        }
       		for(int i=101;i<licznik;i++){
       	        	cout<<ta1[i];
       	 	}cout<<endl;
	}
	//wynik
	if(!wiekszypierwszy){cout<<"-";}
	int licznik=0;
	while(t1[licznik]==0){
		licznik++;
	}
	for(int i=licznik;i<=100;i++){
		cout<<t1[i];
	}
	licznik=199;
	while(t1[licznik]==0){
		licznik--;
	}
	for(int i=101;i<licznik;i++){
		cout<<t1[i];
	}cout<<endl;
}
