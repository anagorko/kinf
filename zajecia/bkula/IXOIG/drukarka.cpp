#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;

    string txt[n];
    for (int i = 0; i < n; i++)
    {
        cin >> txt[i];
    }

    sort(txt, txt + n);

    int best = 1;
    int prev = 1;


    for (int i = 1; i < n; i++)
    {
    	if (txt[i-1].size() <= txt[i].size())
    	{
    		bool b = true;
    		for (int j = 0; j < txt[i-1].size(); j++)
    		{
    			if (txt[i-1][j] != txt[i][j])
    			{
    				b = false;
    				break;
    			}
    		}
    		if (b) prev++;
    	}
    	else
    	{
    		prev = 1;
    	}
    	best = max(best, prev);
    }

    cout << best << endl;
}






























