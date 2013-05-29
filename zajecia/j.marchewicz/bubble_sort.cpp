// (C) Marchewa
#include <iostream>
using namespace std;
int main()
{

	int q;
	int w;
	bool b = false;

	cin>>q;

	int l[q];

	for (int i = 0; i != q; i++)
	{
		cin>>l[i];
	}

for (; b != true;)
	{
		b = true;
		for (int i = 0; i != q - 1; i++)
		{
			if (l[i] > l[i + 1])
			{
				w = l[i];
				l[i] = l[i + 1];
				l[i + 1] = w;
				b = false;
			}
		}
	}

for (int i = 0; i != q; i++)
	{
		cout<<l[i]<< endl;
	}

return 0;
}
