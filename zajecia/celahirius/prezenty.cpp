#include <iostream>

using namespace std;

int main()
{
    int a,b,n, w1, w2, w3, k=0;

    cin>>a>>b>>n;

    int bol[n];

    for(int i=0; i<n; i++)
    {
        cin>>w1>>w2>>w3;
        if(w1<=a && w2<=b || w2<=a && w1<=b || w3<=a && w1<=b || w3<=a && w2<=b || w2<=a && w3<=b || w1<=a && w3<=b)
        {
            bol[i]=1;
        }
        else
        {
            bol[i]=0;
            k++;
        }
    }
    for(int j=0; j<n; j++)
    {
        if(bol[j]==1)
        {
            cout<<"TAK"<<endl;
        }
        else
        {
            cout<<"NIE"<<endl;
        }
    }
    cout<<k;

    return 0;
}
