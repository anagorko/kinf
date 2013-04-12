#include <iostream>
#include <cmath> //albo math.h ale ja wolę cmath - 
using namespace std;
int main ()
{
    int n;
    cin >> n;

    for (int i = 1; i < sqrt(n); i++) 
      if (n % i == 0)
        {
          cout << i << endl;
	}

    for (int i = sqrt(n); i >= 1; i--) 
      if (n % i == 0)
        {
          cout << n/i << endl;
	}
                     
    return 0;
}
