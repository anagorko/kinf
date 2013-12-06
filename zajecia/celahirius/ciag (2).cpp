#include <iostream>

using namespace std;

int main()
{
    int n,p=0;

    cin>>n;

    int ciag[n];

    for(int i=0;i<n;i++)
    {
        cin>>ciag[i];
    }
    for(int i=0;i<n;i++)
    {
        p=(ciag[i]+ciag[i+1]+1)+(ciag[i]*ciag[i+1]);
        ciag[i+1]=p;
    }

    cout<<p;

    return 0;
}
