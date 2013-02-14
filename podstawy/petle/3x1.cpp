#include<iostream>
using namespace std;

int main()
{
  int x;
  
  cin >> x;
  
  while (x != 1) {
    if (x % 2 == 0) {
      x = x / 2;
    } else {
      x = 3 * x + 1;
    }
    cout << x << endl;

    usleep(1000000);
  }
  
  cout << endl;
  
  return 0;
}
