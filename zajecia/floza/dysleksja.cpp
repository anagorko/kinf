#include <iostream>
#include <string>
using namespace std;

int main()
{
	string t1, t2;
	int n, i = 0;

	cin>>n;
	cin>>t1;
	cin>>t2;

	for (; n != 0; n--) {
		if (t1[n-1] != t2[n-1]) {
			i++;
		}
	}

	cout<<i;

	return 0;
}
