#include<stdlib.h>
#include<iostream>
using namespace std;

int main()
{
    srandom(time(NULL)+getpid());
	int n = 0;
	for(int i = 0; i < 20; i++){
		n = (random() % 2);
		if(n == 0){
		cout << "O" << endl; 
		}else{
		cout << "R" << endl;
		}
	}
    return 0;
}
