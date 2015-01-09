#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(0);
	
	int n;
	cin >> n;
	int maxc = 0, minc = 2001;
	for (int i = 0; i < n; i++)
	{
		int c;
		cin >> c;
		maxc = max(c, maxc);
		minc = min(c, minc);
	}
	
	cout << maxc - minc << endl;
}
