#include <iostream>
using namespace std;
int main () 
{
      int a;
      cout << "Podaj rozłożenie płóz helikoptera\n";
      cin >> a;
      for (int i = 0; i<a/2; i++){
          cout << "H";
             for (int j = 0; j<a-2; j++){
             	cout << " ";
             }
           cout << "H";
           cout << "\n";
      }
      for (int k = 0;k<a; k++){
      cout << "H";
      }
      cout << "\n";
      for (int i = 0; i<a/2; i++){
          cout << "H";
             for (int j = 0; j<a-2; j++){
             	cout << " ";
             }
           cout << "H";
           cout << "\n";
      }


cout << endl;
return 0;
}
