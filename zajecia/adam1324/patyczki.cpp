#include<iostream>
using namespace std;
int main(){
int a,s,d;
cin s;
cin a;
cin d;
if(a+s>d && a+d>s && s+d>a){
	cout<<"może trójkąt."endl;
	if(s==d==a)
		cout<<"może trójkat równoboczny."
	}else{
		cout<<"nie może"endl;
	}
	if(a==s || a==d || s==d){
		cout<<"może trójkątrówno."endl;
	}else{
		cout<<"nie może"endl;
	}
	if(a*a+s*s==d*d || a*a+d*d==s*s || s*s+d*d>a*a){
		cout<<"może trójkąt prostokątny."endl;
	}
}else{
	cout<<"nic nie może"endl;
}
return 0;
}
