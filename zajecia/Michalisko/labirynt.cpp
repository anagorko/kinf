#include<iostream>
using namespace std;

int main(){
	int a, b, K[2], c=1;
	cin >> a >> b;
	int m[a][b];
	for(int a_=0; a_<a; a_++){
		for(int b_= 0; b_<b; b_++){
			char tmp;

			cin >> tmp;
			if(tmp =='#')
				m[a_][b_]=-1;
			else if(tmp =='.')
				m[a_][b_]=0;
			else if(tmp =='P')
				m[a_][b_]=1;
			else if(tmp =='K')
				m[a_][b_]=0;
				K[0]=a_;
				K[1]=b_;
		}
	}
	while (m[K[0]][K[2]] == 0) {
		for(int a_=0; a_<a; a_++){
			for(int b_= 0; b_<b; b_++){
				if(m[a_][b_]==c){
					if(m[a_+1][b_]==0)
						m[a_+1][b_]=c+1;
					if(m[a_][b_+1]==0)
						m[a_][b_+1]=c+1;
					if(m[a_-1][b_]==0)
						m[a_-1][b_]=c+1;
					if(m[a_][b_-1]==0)
						m[a_][b_-1]=c+1;

				}
			}
		}
		c++;
	}

	cout << m[K[0]][K[1]];
}
