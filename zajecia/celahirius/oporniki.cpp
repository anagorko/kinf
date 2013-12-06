#include <iostream>
#include <math.h>
#include<iomanip>

using namespace std;

int main()
{
    float U, U2, k,k2, P;

    cin>>U>>k;
    k2=k+1;
    U2=U*U;

    P=k2*k2*k2/k*U2/200;
    cout<<setprecision(5)<<P;

    return 0;
}
