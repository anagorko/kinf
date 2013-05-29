#include<iostream>
using namespace std;

typedef struct koniec
{
  int l;
  bool p;
};

koniec a[1000000];

int main()
{
  int n;
  cin >> n;
  
  for (int i = 0; i < 2*n; i++) {
    cin >> a[i].l; a[i].p = true;
    i++;
    cin >> a[i].l; a[i].p = false;
  }
  
  n = 2 * n;
  
  for (int i = 0; i < n; i++) {
    int min = a[i].l;
    int min_i = i;
    for (int j = i; j < n; j++) {
      if (a[j].l < min || a[j].l == min && !a[j].p) {
        min_i = j;
        min = a[j].l;
      }
    }
    
    koniec k = a[i];
    a[i] = a[min_i];
    a[min_i] = k;
  }

  int ile_os = 0;
  
  for (int i = 0; i < n; i++) {
    if (a[i].p) {
      ile_os++;
    } else {
      ile_os--;
    }
    
    cout << "Jest osób: " << ile_os << endl;
  }
}
