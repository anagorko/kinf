#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
const int n = 20;

srandom(getpid());

vector<int> v;

	for (int i = 0; i < n; i++) {
		v.push_back((random() % 900) + 100);
	}
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	
	for(const int &i: v) {
		cout << i << " ";
	}
	cout << endl;
}
