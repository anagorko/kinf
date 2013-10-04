#include<iostream>
using namespace std;

void wypisz(int n, string s)
{
    for (int i =0; i < n; i++) {
    cout << s;
    }
}
 
int main()
{
    cout << "  ^\n";
    cout << " / \\\n";
    wypisz(10, "|   |\n");
    cout << " +++++\n";
    cout << " |||||\n";
    return 0;
}
