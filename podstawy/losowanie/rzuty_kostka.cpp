#include<stdlib.h>
#include<iostream>
using namespace std;

int main()
{
    cout << "Wyniki dziesięciokrotnego rzutu kostką: ";
    for (int i = 0; i < 10; i++) {
        cout << (random() % 6 + 1) << " ";
    }
    cout << endl;
    return 0;
}
